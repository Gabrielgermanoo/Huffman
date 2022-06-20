#ifndef tad_test_c
#define tad_test_c

#include <stdio.h>
#include <stdlib.h>


// Structs
typedef struct node Node; 
struct node
{
    int data;
    int priority;
    struct node* next;
};

typedef struct binary_tree tree;
struct binary_tree {
    int item;
    tree *left;
    tree *right;
};


///// codes

/**
 * @brief create a new node
 * 
 * @param d 
 * @param p 
 * @return Node* 
 */
Node *newNode(int d, int p);

/**
 * @brief Removes the element with the highest priority form the list
 * 
 * @param head 
 */
void pop(Node** head);

/**
 * @brief Function to push according to priority
 * 
 * @param head 
 * @param d 
 * @param p 
 */
void push(Node** head, int d, int p);

/**
 * @brief Verifica se está vazia (a fila)
 * 
 * @param head 
 * @return int 
 */
int isEmpty(Node** head);

/**
 * @brief Create a node object
 * 
 * @param pq 
 * @return Node* 
 */
Node *create_node(Node *pq);


/**
 * @brief Create a empty binary tree object
 * 
 * @return tree* 
 */
tree* create_empty_binary_tree();

/**
 * @brief Create a binary tree object
 * 
 * @param item 
 * @param left 
 * @param right 
 * @return tree* 
 */
tree* create_binary_tree(int item, tree *left, tree *right);

#endif