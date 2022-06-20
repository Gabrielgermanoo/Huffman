#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/MyMem.h>
#include "../tad_test/tad_test.h"
#include <stdio.h>
#include <stdlib.h>

Node *NEW_QUEUE = NULL;
tree *NEW_HUFF_ROOT = NULL;

int init_suite(void) {
    return 0;
}

int clean_suite(void) { 
    return 0; 
}

/*
    TO DO:
    Colocar as estruturas em um arquivo .h para poder acessar
    como "Biblioteca" no test 
*/
void test_create_queue()
{
    NEW_QUEUE = create_node(NEW_QUEUE);
    CU_ASSERT_PTR_NULL(NEW_QUEUE);
    CU_ASSERT_FALSE(NEW_QUEUE);
}

void test_push_queue()
{
    NEW_QUEUE = newNode(4, 1);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    CU_ASSERT_EQUAL(NEW_QUEUE->priority, 1);

    push(&NEW_QUEUE, 5, 3);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    CU_ASSERT_EQUAL(NEW_QUEUE->next->priority, 3);

    push(&NEW_QUEUE, 6, 2);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    CU_ASSERT_EQUAL(NEW_QUEUE->next->priority, 2);
}

void test_pop_queue() //dequeue
{

    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    pop(&NEW_QUEUE);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    CU_ASSERT_EQUAL(NEW_QUEUE->data, 6);
    pop(&NEW_QUEUE);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    CU_ASSERT_EQUAL(NEW_QUEUE->data, 5);
    pop(&NEW_QUEUE);
    CU_ASSERT_PTR_NULL(NEW_QUEUE);
}

void test_create_binary_tree()
{
    
    NEW_HUFF_ROOT = create_empty_binary_tree();
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT);
}

// TO DO
void test_generate_binary_tree()
{
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT);
    NEW_HUFF_ROOT = create_binary_tree(6, create_binary_tree(4, NULL, NULL), create_binary_tree(9, create_binary_tree(1, NULL, NULL), create_binary_tree(2, NULL, NULL)));
    
    CU_ASSERT_PTR_NOT_NULL(NEW_HUFF_ROOT);
    CU_ASSERT_EQUAL(NEW_HUFF_ROOT->item, 6);

    CU_ASSERT_PTR_NOT_NULL(NEW_HUFF_ROOT->left);
    CU_ASSERT_EQUAL(NEW_HUFF_ROOT->left->item, 4);
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT->left->left);
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT->left->right);

    CU_ASSERT_EQUAL(NEW_HUFF_ROOT->right->item, 9);
    CU_ASSERT_PTR_NOT_NULL(NEW_HUFF_ROOT->right);
    CU_ASSERT_PTR_NOT_NULL(NEW_HUFF_ROOT->right->left);
    CU_ASSERT_PTR_NOT_NULL(NEW_HUFF_ROOT->right->right);

    CU_ASSERT_EQUAL(NEW_HUFF_ROOT->right->left->item, 1);
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT->right->left->left);
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT->right->left->right);

    CU_ASSERT_EQUAL(NEW_HUFF_ROOT->right->right->item, 2);
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT->right->right->left);
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT->right->right->right);
}
int main()
{
    /*
        Iniciando o CUnit para realizar os testes
    */
    CU_pSuite pSuite = NULL;
    if(CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();
    pSuite = CU_add_suite("Testes Unitários", init_suite, clean_suite);

    if(pSuite == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    //Teste das Estruturas
    if(CU_add_test(pSuite, "\nTestando a Criação da Fila de Prioridade\n", test_create_queue)==NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if(CU_add_test(pSuite, "\nTestando o enfileiramento na Fila de Prioridade.\n", test_push_queue)==NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if(CU_add_test(pSuite,"\nTestando o desenfileiramento na fila de prioridade\n", test_pop_queue) == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
       if(CU_add_test(pSuite,"\nTestando a criação da Árvore de Huffman\n", test_create_binary_tree) == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
       if(CU_add_test(pSuite,"\nTestando a inserção na Árvore de Huffman\n", test_generate_binary_tree) == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_run_tests();
    return CU_get_error();

}

void initialize_test()
{
    printf("Testando estruturas....");
}