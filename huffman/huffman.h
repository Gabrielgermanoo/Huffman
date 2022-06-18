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
 * @brief Função que remove o primeiro item da fila de prioridade
 * @param q 
 * @return tree*
 */
tree *dequeue(queue *q);

/**
 * @brief Função que cria um novo nó na Árvore
 * @param ch byte
 * @param freq
 * @param left 
 * @param right 
 * @return tree*
 */
tree *new_tree_node(byte ch, int freq, tree *left, tree *right);

/**
 * @brief função que cria um novo nó na fila de prioridade
 * @param tree_node
 * @return tree*
 */
node_pq *new_node(tree *tree_node);


/**
 * @brief Função que "libera" a memória gerada pela árvore
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

/**
 * @brief Create a empty huff node object
 * 
 * @return tree* 
 */
tree* create_empty_huff_node();

#endif