#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/MyMem.h>
#include <stdio.h>
#include <stdlib.h>

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

}

void test_push_queue()
{

}

void test_pop_queue() //dequeue
{

}

void test_create_huffman_tree()
{

}

void test_generate_huffman_tree()
{

}

void test_generate_huffman_tree_from_file()
{

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