#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//O unsigned char servirá para representar o byte
typedef unsigned char byte;

//O unsigned char servirá para representar o byte
typedef unsigned char byte;

/*  ÁRVORE DE HUFFMAN
    freq = int
    ch = byte
    left, right = tree*
*/
typedef struct _nodearvore{
    int                    freq;
    byte                   ch;
    struct _nodearvore    *left,*right;
} tree;

// NODE DA FILA DE PRIORIDADE
// node = tree / next = node_pq
typedef struct _priority_queue_node{
    struct _priority_queue_node     *next;
    struct _nodearvore              *node;
} node_pq;

//FILA DE PRIORIDADE
typedef struct _priority_queue{
    node_pq     *head;
    int         tamanho;
} queue;

void compressed_file_header(FILE *arquivo_s, int lixo_mem, int tree_size)
{
    rewind(arquivo_s);
    byte b = lixo_mem;
    b = b << 5;
    b = b | (byte)(tree_size>>8);
    byte seg_b = (byte)tree_size;

    fwrite(&b, sizeof(byte), 1, arquivo_s);   
    fwrite(&seg_b, sizeof(byte), 1, arquivo_s);   
    return;
}

bool codificar(tree *n, byte c, char *buffer, int tamanho)
{
    if (!(n->left || n->right) && n->ch == c)
    {
        buffer[tamanho] = '\0';
        return true;
    }
    else
    {
        bool encontrado = false;

        if (n->left)
        {
            buffer[tamanho] = '0';

            encontrado = codificar(n->left, c, buffer, tamanho + 1);
        }

        if (!encontrado && n->right)
        {
            buffer[tamanho] = '1';
            encontrado = codificar(n->right, c, buffer, tamanho + 1);
        }
        if (!encontrado)
        {
            buffer[tamanho] = '\0';
        }
        return encontrado;
    }

}

void tamanho_arvore_huff(tree* node, int *tamanho, char *string)
{
    if (node == NULL)
        return;
    string[*tamanho] = node->ch;
    *tamanho += 1;
    tamanho_arvore_huff(node->left, tamanho, string);
    tamanho_arvore_huff(node->right, tamanho, string);
}

//Função que remove o primeiro item da fila de prioridade
tree *dequeue(queue *q)
{
    if(!q->tamanho) return NULL;
    node_pq *aux = q->head;
    tree *aux_2 = aux->node;
    
    q->head = aux->next;

    free(aux);
    aux = NULL;
    q->tamanho--;
    return aux_2;
}

node_pq *new_node(tree *tree_node)
{
    node_pq *node = (node_pq*)malloc(sizeof(node_pq));

    node->node = tree_node;
    node->next = NULL;

    return node;
}

tree *new_tree_node(byte ch, int freq, tree *left, tree *right)
{
    tree *new_node = (tree*)malloc(sizeof(tree));

    new_node->freq = freq;
    new_node->ch = ch;
    new_node->left = left;
    new_node->right = right;

    return new_node;
}

//Função que insere um nó na fila de prioridade 
void insert(node_pq *node, queue *q)
{
    if(q->head == NULL || node->node->freq <= q->head->node->freq){
        node->next = q->head;
        q->head = node;
    }
    else{
        node_pq *aux = q->head;
        while(aux->next != NULL){
            if(node->node->freq <= aux->next->node->freq) 
                break;
            aux = aux->next;
        }

        node->next = aux->next;
        aux->next = node;
    }
    q->tamanho++;
}

tree* huffman_tree(unsigned int *bytes)
{
    //Cabeça da fila de prioridade implementada como lista encadeada
    queue queue = {NULL, 0};
    
    for(int i=0; i<256; i++)
    {
        if(bytes[i])
            insert(new_node(new_tree_node(i, bytes[i], NULL, NULL)), &queue);
    }

    bool flag_insert = false;
    while(queue.tamanho > 1 || !flag_insert)
    {
        tree *left_child = dequeue(&queue);
        tree *right_child = dequeue(&queue);
        tree *soma = new_tree_node('*', (left_child == NULL ? 0 : left_child->freq) + 
        (right_child == NULL ? 0 : right_child->freq), left_child, right_child);
        insert(new_node(soma), &queue);

        flag_insert = true;
    }
    
    return (queue.head == NULL ? NULL : dequeue(&queue));
    
}

//Função que scaneia o arquivo e armazena no array "bytes" as frequências de cada byte scaneado
void buscando_frequencias(FILE *entrada, unsigned int *bytes)
{
    byte b;
    while(fread(&b, 1, 1, entrada))
        bytes[(byte)b]++;
    //void rewind(FILE *stream) = volta a stream FILE *entrada para o começo do arquivo
    rewind(entrada); 
}

//Função que exibe uma mensagem de erro caso o programa não consiga localizar um arquivo e em seguida o encerra
void error_file()
{
    printf("--------------------\nErro ao encontrar o arquivo, por favor verifique se o arquivo esta no diretorio correto\n--------------------");
    exit(EXIT_SUCCESS);
}

void free_huffman_tree(tree *node)
{
    //caso base da recursão
    if(!node) return;
    else
    {
        tree *left = node->left;
        tree *right = node->right;
        free(node);
        free_huffman_tree(left);
        free_huffman_tree(right);
    }
}

//TO DO: FAZER ESSA FUNÇÃO
void comprimir(const char *entrada, const char *saida)
{
    unsigned int bytes[256] = {0};
    tree *hufftree;
    byte null = 0;

    FILE *arquivo_e = fopen(entrada, "rb");
    if(!arquivo_e)
        error_file();

    FILE *arquivo_s = fopen(saida, "wb");
    if(!arquivo_s)
        error_file();

    buscando_frequencias(arquivo_e, bytes);
    hufftree = huffman_tree(bytes);
    int tamanho_arvore = 0;
    char str[1000] = {'\0'};
    tamanho_arvore_huff(hufftree, &tamanho_arvore, str);

    fwrite(&null, 2, 1, arquivo_s);

    for(int i=0; i<1000; i++)
    {
        char c = str[i];
        if(c == '\0')
            break;
        fwrite(&c, 1, 1, arquivo_s);
    }

    byte ch, aux = 0;
    unsigned int tamanho = 0;
    while (fread(&ch, 1, 1, arquivo_e) >= 1)
    {
        char buffer[1024] = {0};
    
        codificar(hufftree, ch, buffer, 0);

        // Laço que percorre o buffer
        for (int i = 0; i < strlen(buffer); i++)
        {
            if(buffer[i] == '1')
                aux = aux | 128 >> tamanho;

            tamanho++;

            if(tamanho % 8 == 0){
                fwrite(&aux, 1, 1, arquivo_s);
                aux = 0;
                tamanho = 0;
            }
        }
    }

    // Escreve no arquivo o que sobrou
    if(!(tamanho==0))
        fwrite(&aux, 1, 1, arquivo_s);

    compressed_file_header(arquivo_s, 8-tamanho, tamanho_arvore);
    fclose(arquivo_e);
    fclose(arquivo_s);

}

//TO DO: FAZER ESSA FUNÇÃO
void descomprimir(const char *entrada, const char *saida)
{
    tree *raiz = NULL;
    unsigned int bytes[256] = {0};

    FILE *arquivo_e = fopen(entrada, "rb");
    if(!arquivo_e)
        error_file();

    FILE *arquivo_s = fopen(saida, "wb");
    if(!arquivo_s)
        error_file();
    
}
//Função que printa no terminal o uso correto do programa caso tenha sido chamado de forma incorreta
void error_param()
{
    printf("--------------------\nUso invalido!\nModelo de uso: ./huffman [-c OU -d] [ARQ. DE ENTRADA] [ARQ. DE SAIDA]\n\n-c: Comprime um arquivo; ARQ. DE SAIDA deve ser .huffman\n");   
    printf("-d: Descomprime um arquivo; ARQ. DE ENTRADA deve ser .huffman\n--------------------");
}


// MAIN FUNCTION
// MAIN
// argc = inteiro que contém a quantidade de parâmetros passados para o programa
// argv[] = array de strings que contém os parâmetros passados para o programa
int main(int argc, char *argv[])
{
    if(argc < 4){
        error_param();
        return 0;
    }
    if(!strcmp("-c", argv[1])){
        if(strstr(argv[3], ".huffman"))
            comprimir(argv[2], argv[3]);
        else
            error_param();
    }
    else if (!strcmp("-d", argv[1])){
        if(strstr(argv[2], ".huffman"))
            descomprimir(argv[2], argv[3]);
        else
            error_param();
    }
    else
        error_param();
    return 0;
}
