#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nosso pão com manteiga do código, o unsigned char servirá para representar o byte
typedef unsigned char byte;

/*  ÁRVORE DE HUFFMAN
    freq = int
    ch = byte
    left, right = tree*
*/

//TO DO: FAZER ESSA FUNÇÃO
void comprimir(const char *entrada, const char *saida)
{
    printf("%s\n%s\n", entrada, saida);
}

//TO DO: FAZER ESSA FUNÇÃO
void descomprimir(const char *entrada, const char *saida)
{
    printf("%s\n%s\n", entrada, saida);
}


typedef struct _nodearvore{
    void    *freq,
            *ch,
            *left,
            *right;
} tree;

// FILA DE PRIORIDADE
// node = tree / next = node_pq

typedef struct _priority_queue_node{
    void    *node,
            *next;
} node_pq;

// MAIN FUNCTION
// argc = inteiro que contém a quantidade de parâmetros passados para o programa
// argv[] = array de strings que contém os parâmetros passados para o programa

//Função que printa no terminal o uso correto do programa caso tenha sido chamado de forma incorreta
void error_param()
{
    printf("--------------------\nUso invalido!\nModelo de uso: ./huffman [-c OU -d] [ARQ. DE ENTRADA] [ARQ. DE SAIDA]\n\n-c: Comprime um arquivo; ARQ. DE SAIDA deve ser .huffman\n");   
    printf("-d: Descomprime um arquivo; ARQ. DE ENTRADA deve ser .huffman\n--------------------");
}

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