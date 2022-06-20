#include "tad_test.h"

// Function to Create A New Node
Node* newNode(int d, int p)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
 
    return temp;
}

void pop(Node** head)
{
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}

void push(Node** head, int d, int p)
{
    Node* start = (*head);

    Node* temp = newNode(d, p);

    if ((*head)->priority > p) {
 
        temp->next = *head;
        (*head) = temp;
    }
    else {

        while (start->next != NULL &&
            start->next->priority < p) {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}

Node *create_node(Node *pq)
{
    return (pq = NULL);
}

tree* create_empty_binary_tree()
{
    return NULL;
}

tree* create_binary_tree(int item, tree *left, tree *right)
    {
    tree *new_binary_tree =(tree*) malloc(sizeof(tree));
    new_binary_tree->item = item;
    new_binary_tree->left = left;
    new_binary_tree->right = right;
    return new_binary_tree;
}