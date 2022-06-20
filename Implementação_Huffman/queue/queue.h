#ifndef priority_queue_h
#define priority_queue_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../util/util.h"
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
    struct _nodearvore *node;
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

#include "../huffman/huffman.h"

/**
 * @brief Função que insere um nó na fila de prioridade 
 * @param node
 * @param q
 */
void insert(node_pq *node, queue *q);


#endif