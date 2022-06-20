#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/MyMem.h>
#include "../queue/queue.h"
#include "../huffman/huffman.h"
#include "../util/util.h"
#include <stdio.h>
#include <stdlib.h>

node_pq *NEW_QUEUE = NULL;
tree *NEW_HUFF_ROOT = NULL;
queue QUEUE = {NULL, 0};

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
    NEW_QUEUE = new_node(NEW_HUFF_ROOT);
    CU_ASSERT_PTR_NULL(NEW_QUEUE->next);
    CU_ASSERT_FALSE(NEW_QUEUE->node);
}

void test_push_queue()
{
    queue queue_aux = QUEUE;
    int frequency = 15;
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    tree *AUX_NODE = new_tree_node('A', frequency, NULL, NULL);
    CU_ASSERT_PTR_NULL(AUX_NODE->left);
    CU_ASSERT_PTR_NULL(AUX_NODE->right);

    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    NEW_QUEUE = new_node(AUX_NODE);
    insert(NEW_QUEUE, &QUEUE);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    CU_ASSERT_EQUAL(NEW_QUEUE->node->freq, AUX_NODE->freq);
    CU_ASSERT_EQUAL(NEW_QUEUE->node->ch, 'A');
    CU_ASSERT_EQUAL(QUEUE.tamanho, 1);

    frequency = 10;
    CU_FREE(AUX_NODE);

    AUX_NODE = new_tree_node('B', frequency, NULL, NULL);
    CU_ASSERT_PTR_NULL(AUX_NODE->left);
    CU_ASSERT_PTR_NULL(AUX_NODE->right);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);

    NEW_QUEUE = new_node(AUX_NODE);
    insert(NEW_QUEUE, &QUEUE);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    CU_ASSERT_EQUAL(NEW_QUEUE->node->freq, AUX_NODE->freq);
    CU_ASSERT_EQUAL(NEW_QUEUE->node->ch, 'B');
    CU_ASSERT_EQUAL(QUEUE.tamanho, 2);
    

    frequency = 9;
    CU_FREE(AUX_NODE);

    AUX_NODE = new_tree_node('C', frequency, NULL, NULL);
    CU_ASSERT_PTR_NULL(AUX_NODE->left);
    CU_ASSERT_PTR_NULL(AUX_NODE->right);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);

    NEW_QUEUE = new_node(AUX_NODE);
    insert(NEW_QUEUE, &QUEUE);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    
    CU_ASSERT_EQUAL(NEW_QUEUE->node->freq, AUX_NODE->freq);
    CU_ASSERT_EQUAL(NEW_QUEUE->node->ch, 'C');
    CU_ASSERT_EQUAL(QUEUE.tamanho, 3);
}

//TO DO
void test_pop_queue() //dequeue
{
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    NEW_QUEUE = QUEUE.head;
    tree *AUX_NODE = dequeue(&QUEUE);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    //CU_ASSERT_EQUAL(AUX_NODE->freq, 9);
    CU_ASSERT_EQUAL(QUEUE.tamanho, 2);

    NEW_QUEUE = QUEUE.head;
    AUX_NODE = dequeue(&QUEUE);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    //CU_ASSERT_EQUAL(AUX_NODE->freq, 9);
    CU_ASSERT_EQUAL(QUEUE.tamanho, 1);
    
    NEW_QUEUE = QUEUE.head;
    AUX_NODE = dequeue(&QUEUE);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    //CU_ASSERT_EQUAL(AUX_NODE->freq, 9);
    CU_ASSERT_EQUAL(QUEUE.tamanho, 0);

}

void test_create_huffman_tree()
{
    NEW_HUFF_ROOT = create_empty_huff_node();
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT);
}

// TO DO
void test_generate_huffman_tree()
{
    long long int frequency = 10000;
    unsigned long bytes[256] = {0};
    insert(new_node(new_tree_node('A', frequency, NULL, NULL)), &QUEUE);
    NEW_QUEUE = QUEUE.head;
    frequency = 9000;
    insert(new_node(new_tree_node('B', frequency, NULL, NULL)), &QUEUE);
    NEW_QUEUE->next = QUEUE.head->next;
    frequency = 8000;
    insert(new_node(new_tree_node('C', frequency, NULL, NULL)), &QUEUE);
    NEW_QUEUE->next->next = QUEUE.head->next->next;
    frequency = 10000;
    insert(new_node(new_tree_node('D', frequency, NULL, NULL)), &QUEUE);
    NEW_QUEUE->next->next->next = QUEUE.head->next->next->next;
    NEW_HUFF_ROOT = NEW_QUEUE->node;
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE->next);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE->next->next);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE->next->next->next);

    //CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT);
    print_huff_pre_order(NEW_HUFF_ROOT);

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
       if(CU_add_test(pSuite,"\nTestando a criação da Árvore de Huffman\n", test_create_huffman_tree) == NULL)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
       if(CU_add_test(pSuite,"\nTestando a inserção na Árvore de Huffman\n", test_generate_huffman_tree) == NULL)
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