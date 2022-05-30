#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef unsigned char byte;

typedef struct _nodearvore
{
    int freq;
    byte ch;
    void *left, *right;
} tree;