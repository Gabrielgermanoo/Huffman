#include "huffman.h"

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