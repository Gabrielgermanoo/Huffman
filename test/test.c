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
    queue queue = {NULL, 0};

    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    tree *AUX_NODE = new_tree_node('A', frequency, NULL, NULL);
    CU_ASSERT_PTR_NULL(AUX_NODE->left);
    CU_ASSERT_PTR_NULL(AUX_NODE->right);

    CU_ASSERT_PTR_NOT_NULL(NEW_QUEUE);
    node_pq *AUX_PQ = new_node(AUX_NODE) ;
    insert(AUX_PQ, &queue);
    CU_ASSERT_PTR_NOT_NULL(AUX_PQ);
}

void test_pop_queue() //dequeue
{
    
}

void test_create_huffman_tree()
{
    NEW_HUFF_ROOT = create_empty_huff_node();
    CU_ASSERT_PTR_NULL(NEW_HUFF_ROOT);
}

void test_generate_huffman_tree()
{

}

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