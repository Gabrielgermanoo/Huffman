#ifndef decompress_h
#define decompress_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../queue/queue.h"
#include "../huffman/huffman.h"
#include "../util/util.h"

/**
 * @brief Função para descomprimir o cabeçalho a partir do lixo de memória e do tamanho da árvore informado no file
 * 
 * @param arquivo_e 
 * @param tree_size 
 * @param trash_size 
 */
void header_decompress(FILE *arquivo_e, short int *tree_size, short int *trash_size);

/**
 * @brief Função para descomprimir o arquivo a partir do header
 * 
 * @param entrada 
 * @param saida 
 */
void descomprimir(const char *entrada, const char *saida);

#endif