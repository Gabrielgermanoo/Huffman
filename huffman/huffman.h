#ifndef huffman_h
#define huffman_h

#include <stdio.h>
#include <stdlib.h>
#include "../queue/queue.h"
#include "../util/util.h"

// Structs

/**
 * @brief Nós da Arvore
 * 
 */
typedef struct _nodearvore tree;
struct _nodearvore{
    int                   freq;
    byte                   ch;
    struct _nodearvore    *left,*right;
};

////

/**
 * @brief Função que escreve no arquivo de saída 
 * @param saida arquivo de saída
 * @param node nó da arvore
 * @param x
 */
void tamanho_arvore_huff(FILE *saida, tree* node, short *x);

/**
 * @brief Função que constrói a árvore de huffman através das frequências
 * 
 * @param bytes 
 * @return tree* 
 */
tree* huffman_tree(unsigned long *bytes);

/**
 * @brief 
 * 
 * @param node 
 */
void free_huffman_tree(tree *node);

/**
 * @brief Reconstrói a árvore de huffman através do arquivo comprimido
 * 
 * @param string_tree 
 * @param x 
 * @return tree* 
 */
tree* rebuild_hufftree(char *string_tree, short *x);

#endif