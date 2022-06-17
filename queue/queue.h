#ifndef priority_queue_h
#define priority_queue_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/util.h"
#include "../huffman/huffman.h"
/*
    Structs
*/

/**
 * @brief Nó da fila de prioridade
 * 
 */
typedef struct _priority_queue_node node_pq;
struct _priority_queue_node
{
    struct _priority_queue_node *next;
    struct _nodearvore *node
};

/**
 * @brief Estrutura padrão da fila
 * 
 */
typedef struct _priority_queue queue;
struct _priority_queue
{
    node_pq *head;
    int tamanho;
};

/**
 * @brief Função que insere um nó na fila de prioridade 
 * @param node
 * @param q
 */
void insert(node_pq *node, queue *q);

/**
 * @brief função que cria um novo nó na fila de prioridade
 * @param tree_node
 * @return tree*
 */
node_pq *new_node(tree *tree_node);

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

#endif