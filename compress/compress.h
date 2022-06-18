#ifndef compress_h
#define compress_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../queue/queue.h"
#include "../util/util.h"
#include "../huffman/huffman.h"

/**
 * @brief Função que "escreve" o header sendo os dois primeiros bytes o lixo e o restante o tamanho da árvore
 * 
 * @param arquivo_s 
 * @param lixo_mem 
 * @param tree_size 
 */
void header_compress(FILE *arquivo_s, int lixo_mem, int tree_size);

/**
 * @brief Verifica o "caminho" (left, right) 
 * 
 * @param n 
 * @param c 
 * @param buffer 
 * @param tamanho 
 * @return int 
 */
int codificar(tree *n, byte c, char *buffer, int tamanho);


/**
 * @brief Comprime o arquivo selecionado e escreve o output no arquivo X.huffman
 * 
 * @param entrada 
 * @param saida 
 */
void comprimir(const char *entrada, const char *saida);

#endif