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

#endif