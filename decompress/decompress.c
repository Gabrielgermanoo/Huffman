#include "decompress.h"

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
    printf("------------------------------------------------------------\n ,--.  ,--.,--. ,--.,------.,------.,--.   ,--.  ,---.  ,--.  ,--.\n |  '--'  ||  | |  ||  .---'|  .---'|   `.'   | /  O  \\ |  ,'.|  |\n |  .--.  ||  | |  ||  `--, |  `--, |  |'.'|  ||  .-.  ||  |' '  |\n |  |  |  |'  '-'  '|  |`   |  |`   |  |   |  ||  | |  ||  | `   |\n `--'  `--' `-----' `--'    `--'    `--'   `--'`--' `--'`--'  `--'\n\nIniciando descompressao...\n");
    header_decompress(arquivo_e, &tree_size, &trash_size);
    fread(string_tree, 1, tree_size, arquivo_e);
    
    //Após a árvore ter sido reconstruida, cria-se uma árvore auxiliar(huff_nav) que será utilizada para navegar com o 
    //buffer_byte até encontrar uma folha
    hufftree = rebuild_hufftree(string_tree, &mark);
    tree *huff_nav = hufftree;
    
    byte buffer_byte = fgetc(arquivo_e), 
         aux =         fgetc(arquivo_e);
    while(1)
    {
        if(feof(arquivo_e))     
            break;

        for(int i=7; i>=0; i--)
        {
            if(is_bit_set(buffer_byte, i))
                huff_nav = huff_nav->right;
            else
                huff_nav = huff_nav->left;
            if(huff_nav->right == NULL && huff_nav->left == NULL){
                fwrite(&huff_nav->ch, 1, 1, arquivo_s);
                huff_nav = hufftree;
            }
        }
        buffer_byte = aux;
        aux = fgetc(arquivo_e);
    }
    for(int i=7; i>=trash_size; i--)
    {
            if(is_bit_set(buffer_byte, i))
                huff_nav = huff_nav->right;
            else
                huff_nav = huff_nav->left;
            if(huff_nav->right == NULL && huff_nav->left == NULL){
                fwrite(&huff_nav->ch, 1, 1, arquivo_s);
                huff_nav = hufftree;
            }
    }
    printf("Descompressao concluida! Confira o arquivo descomprimido em %s\n------------------------------------------------------------", saida);
    free_huffman_tree(hufftree);
    fclose(arquivo_e);
    fclose(arquivo_s);
    
}