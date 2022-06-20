#include "compress.h"

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

void comprimir(const char *entrada, const char *saida)
{
    
    unsigned long bytes[256] = {0};
    tree *hufftree = NULL;
    byte escape = '\\';
    byte null = 0;

    FILE *arquivo_e = fopen(entrada, "rb");
    if(!arquivo_e)
        error_file();

    FILE *arquivo_s = fopen(saida, "wb");
    if(!arquivo_s)
        error_file();
    
    printf("------------------------------------------------------------\n ,--.  ,--.,--. ,--.,------.,------.,--.   ,--.  ,---.  ,--.  ,--.\n |  '--'  ||  | |  ||  .---'|  .---'|   `.'   | /  O  \\ |  ,'.|  |\n |  .--.  ||  | |  ||  `--, |  `--, |  |'.'|  ||  .-.  ||  |' '  |\n |  |  |  |'  '-'  '|  |`   |  |`   |  |   |  ||  | |  ||  | `   |\n `--'  `--' `-----' `--'    `--'    `--'   `--'`--' `--'`--'  `--'\n\nIniciando compressao...\n");
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
    printf("Compressao concluida! Confira o arquivo comprimido em %s\n------------------------------------------------------------", saida);
    fclose(arquivo_e);
    fclose(arquivo_s);

}