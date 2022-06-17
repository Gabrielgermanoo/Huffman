#include "queue.h"

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