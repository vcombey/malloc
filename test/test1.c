#include "malloc.h"
#include <stdio.h>

int main()
{
    int i;
    int j;
    int k;
    char *addr;

    i = 0;
    printf("stack: %zu\n", (size_t)&i);
    printf("stack: %zu\n", (size_t)&j);
    printf("stack: %zu\n", (size_t)&k);

    while (i < 1024)
    {
        addr = (char*)malloc(1024);
        printf("adrr : %zu\n", (size_t)addr);
        addr[0] = 42;
        i++;
    }
    return (0);
} 
