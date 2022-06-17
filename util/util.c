#include "util.h"

int is_bit_set(byte b, int x)
{
    byte mask = 1 << x;
    return mask & b; 
}

unsigned long long int get_file_size(char *filename)
{
	FILE *fp = fopen(filename, "r");
	fseek(fp, 0L, SEEK_END);
	unsigned long long int size = ftell(fp);
	fclose(fp);
	return size;
}

void buscando_frequencias(FILE *entrada, unsigned long *bytes)
{
    byte b;
    while(fread(&b, 1, 1, entrada))
        bytes[b]++;
    //void rewind(FILE *stream) = volta a stream FILE *entrada para o começo do arquivo
    rewind(entrada); 
    return;
}

void error_file()
{
    printf("--------------------\nErro ao encontrar o arquivo, por favor verifique se o arquivo esta no diretorio correto\n--------------------");
    exit(EXIT_SUCCESS);
}