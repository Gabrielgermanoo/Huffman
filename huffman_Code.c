#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//O unsigned char servirá para representar o byte
typedef unsigned char byte;

/*  ÁRVORE DE HUFFMAN
    freq = int
    ch = bytef
    left, right = tree*
*/
typedef struct _nodearvore{
    int                   freq;
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

void header_compress(FILE *arquivo_s, int lixo_mem, int tree_size)
{
    rewind(arquivo_s);
    byte b = lixo_mem;
    b = b << 5;
    b = b | tree_size >> 8;
    byte seg_b = tree_size;

    fwrite(&b, sizeof(byte), 1, arquivo_s);   
    fwrite(&seg_b, sizeof(byte), 1, arquivo_s);   
    return;
}

void header_decompress(FILE *arquivo_e, short int *tree_size, short int *trash_size)
{
    byte header[2];
    header[1] = fgetc(arquivo_e);
	header[0] = fgetc(arquivo_e);

    byte tr = header[1] >> 5;
    memcpy(trash_size, &tr, 1);

	header[1] = header[1] << 3;
	header[1] = header[1] >> 3;

	memcpy(tree_size, header, 2);
}

int codificar(tree *n, byte c, char *buffer, int tamanho)
{
    if ((n->left == NULL || n->right == NULL) && n->ch == c){
        buffer[tamanho] = '\0';
        return 1;
    }
    else{
        int encontrado = 0;

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

void tamanho_arvore_huff(FILE *saida, tree* node, short *x)
{
    if (node == NULL)
        return;
    char escape = '\\';
    if((node->left == NULL && node->right == NULL) && (node->ch == '*' || node->ch == '\\')){
        ++*x;
        fwrite(&escape, 1, 1, saida);
    }

    ++*x;
    fwrite(&node->ch, 1, 1, saida);

    tamanho_arvore_huff(saida, node->left, x);
    tamanho_arvore_huff(saida, node->right, x);
    return;
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
    return;
}

//Constrói a árvore de huffman através das frequências
tree* huffman_tree(unsigned long *bytes)
{
    //fila de prioridade implementada como lista encadeada
    queue queue = {NULL, 0};
    
    //Passa pelo array de bytes e adiciona as frequências
    for(int i=0; i<256; i++)
    {
        if(bytes[i])
            insert(new_node(new_tree_node(i, bytes[i], NULL, NULL)), &queue);
    }

    int flag_insert = 0;
    while(queue.tamanho > 1 || !flag_insert)
    {
        tree *left_child = dequeue(&queue);
        tree *right_child = dequeue(&queue);
        tree *soma = new_tree_node('*', (left_child == NULL ? 0 : left_child->freq) + 
        (right_child == NULL ? 0 : right_child->freq), left_child, right_child);
        insert(new_node(soma), &queue);

        flag_insert = 1;
    }
    return queue.head->node;
}

//Função que scaneia o arquivo e armazena no array "bytes" as frequências de cada byte scaneado
void buscando_frequencias(FILE *entrada, unsigned long *bytes)
{
    byte b;
    while(fread(&b, 1, 1, entrada))
        bytes[b]++;
    //void rewind(FILE *stream) = volta a stream FILE *entrada para o começo do arquivo
    rewind(entrada); 
    return;
}

//Função que exibe uma mensagem de erro caso o programa não consiga localizar um arquivo e em seguida o encerra
void error_file()
{
    printf("--------------------\nErro ao encontrar o arquivo, por favor verifique se o arquivo esta no diretorio correto\n--------------------");
    exit(EXIT_SUCCESS);
}

//Libera a memória da árvore de huffman
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
    return;
}

//Comprime o arquivo selecionado e escreve o output no arquivo X.huffman
void comprimir(const char *entrada, const char *saida)
{
    unsigned long bytes[256] = {0};
    tree *hufftree = NULL;
    byte escape = '\\';
    byte null = 0;

    FILE *arquivo_e = fopen(entrada, "rb");
    if(!arquivo_e)
        error_file();
    FILE *arquivo_t = fopen("decompresstest.txt", "wb");
    FILE *arquivo_s = fopen(saida, "wb");
    if(!arquivo_s)
        error_file();
    printf("--------------------\nIniciando compressao...\n");

    buscando_frequencias(arquivo_e, bytes);
    hufftree = huffman_tree(bytes);

    short tamanho_arvore = 0;
    
    fwrite(&null, 2, 1, arquivo_s);
    tamanho_arvore_huff(arquivo_s, hufftree, &tamanho_arvore);

    byte ch;
    byte aux = 0;
    short tamanho = 0;
    while (fread(&ch, 1, 1, arquivo_e) >= 1)
    {
        char buffer[1024] = {'0'};
    
        codificar(hufftree, ch, buffer, 0);
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
    if(tamanho > 0)
        fwrite(&aux, 1, 1, arquivo_s);

    free_huffman_tree(hufftree);
    header_compress(arquivo_s, (tamanho > 0) ? 8 - tamanho : 0, tamanho_arvore);
    printf("Compressao concluida! Confira o arquivo comprimido em %s\n--------------------", saida);
    fclose(arquivo_e);
    fclose(arquivo_s);

}

//Reconstrói a árvore de huffman através do arquivo comprimido
tree* rebuild_hufftree(char *string_tree, short *x)
{
    if(string_tree[*x] == '*'){
        ++*x;
        tree *left_child = rebuild_hufftree(string_tree, x);
        ++*x;
        return new_tree_node('*', 0, left_child, rebuild_hufftree(string_tree, x));
    }
    else if(string_tree[*x] == '\\'){
        ++*x;
        return new_tree_node(string_tree[*x], 0, NULL, NULL);
    }
    return new_tree_node(string_tree[*x], 0, NULL, NULL);
}


//TO DO: FAZER ESSA FUNÇÃO
void descomprimir(const char *entrada, const char *saida)
{
    tree *hufftree = NULL;
    short tree_size = 0, trash_size = 0, mark = 0;
    char string_tree[513] = {0};

    FILE *arquivo_e = fopen(entrada, "rb");
    if(!arquivo_e)
        error_file();

    FILE *arquivo_s = fopen(saida, "wb");
    if(!arquivo_s)
        error_file();

    header_decompress(arquivo_e, &tree_size, &trash_size);
    fread(string_tree, 1, tree_size, arquivo_e);
    
    //Após a árvore ter sido reconstruida, cria-se uma árvore auxiliar(huff_nav) que será utilizada para navegar com o 
    //buffer_byte até encontrar uma folha
    hufftree = rebuild_hufftree(string_tree, &mark);
    tree *huff_nav = hufftree;
    
    byte buffer_byte;
    while(1)
    {
        buffer_byte = fgetc(arquivo_e);
        if(feof(arquivo_e))
            break;
        fwrite(&buffer_byte, 1, 1, arquivo_s);
    }
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
    if(argc < 4 || argc > 4){
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
