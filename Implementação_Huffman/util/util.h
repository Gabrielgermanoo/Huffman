#ifndef util_h
#define util_h

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Tipo padrão para armazenar os bytes
 * 
 */
typedef unsigned char byte;

/**
 * @brief Verifica o estado do bit de posição 'i' de um dado Byte
 * @param b 
 * @param i 
 * @return int
 */
int is_bit_set(byte b, int x);

/**
 * @brief Get the file size object
 * 
 * @param filename 
 * @return unsigned long long int 
 */
unsigned long long int get_file_size(char *filename);

/**
 * @brief Função que scaneia o arquivo e armazena no array "bytes" as frequências de cada byte scaneado
 * 
 * @param entrada 
 * @param bytes 
 */
void buscando_frequencias(FILE *entrada, unsigned long *bytes);

/**
 * @brief Função que exibe uma mensagem de erro caso o programa não consiga localizar um arquivo e em seguida o encerra
 * 
 */
void error_file();

/**
 * @brief Função que printa no terminal o uso correto do programa caso tenha sido chamado de forma incorreta
 * 
 */
void error_param();

#endif