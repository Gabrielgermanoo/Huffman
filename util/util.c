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