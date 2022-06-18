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
    int frequency = 15;
    queue queue = {NULL, 0}, queue_a = {NULL, 0}, queue_b = {NULL, 0};

    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    tree *AUX_NODE = new_tree_node('A', frequency, NULL, NULL);
    CU_ASSERT_PTR_NULL(AUX_NODE->left);
    CU_ASSERT_PTR_NULL(AUX_NODE->right);

    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    NEW_QUEUE = new_node(AUX_NODE);
    insert(NEW_QUEUE, &queue);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    CU_ASSERT_EQUAL(NEW_QUEUE->node->freq, AUX_NODE->freq);

    frequency = 10;
    CU_FREE(AUX_NODE);

    AUX_NODE = new_tree_node('B', frequency, NULL, NULL);
    CU_ASSERT_PTR_NULL(AUX_NODE->left);
    CU_ASSERT_PTR_NULL(AUX_NODE->right);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);

    NEW_QUEUE = new_node(AUX_NODE);
    insert(NEW_QUEUE, &queue_a);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    CU_ASSERT_EQUAL(NEW_QUEUE->node->freq, AUX_NODE->freq);

    frequency = 9;
    CU_FREE(AUX_NODE);

    AUX_NODE = new_tree_node('C', frequency, NULL, NULL);
    CU_ASSERT_PTR_NULL(AUX_NODE->left);
    CU_ASSERT_PTR_NULL(AUX_NODE->right);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);

    NEW_QUEUE = new_node(AUX_NODE);
    insert(NEW_QUEUE, &queue_b);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    CU_ASSERT_EQUAL(NEW_QUEUE->node->freq, AUX_NODE->freq);
}

//TO DO
void test_pop_queue() //dequeue
{
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    queue queue = {NULL, 0}, queue_a = {NULL, 0}, queue_b = {NULL, 0};
    tree *AUX_NODE = dequeue(&queue);
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    //CU_ASSERT_EQUAL(AUX_NODE->freq, 9);
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
    queue queue = {NULL, 0};
    insert(new_node(new_tree_node('A', frequency, NULL, NULL)), &queue);
    NEW_QUEUE = queue.head;
    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE)


}
// TO DO
void test_generate_huffman_tree_from_file()
{
    free_huffman_tree(NEW_HUFF_ROOT);
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT);

    NEW_HUFF_ROOT = NULL;
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT);
    FILE *fp = fopen("tests/tree.txt", "rb");
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
       if(CU_add_test(pSuite,"\nTestando a criação da Árvore de Huffman pelo arquivo\n", test_generate_huffman_tree_from_file) == NULL)
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