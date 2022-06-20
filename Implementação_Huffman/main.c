#include "compress/compress.h"
#include "decompress/decompress.h"
#include "util/util.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    if(argc < 4 || argc > 4){
        error_param();
        return 0;
    }
    if(!strcmp("-c", argv[1])){
        if(strstr(argv[3], ".huffman")){
            comprimir(argv[2], argv[3]);
        }
        else
            error_param();
    }
    else if (!strcmp("-d", argv[1])){
        if(strstr(argv[2], ".huffman"))
            descomprimir(argv[2], argv[3]);
        else
            error_param();
    }
    else
        error_param();
    return 0;
}