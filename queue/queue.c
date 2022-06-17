#include "queue.h"

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