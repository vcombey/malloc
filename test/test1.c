#include "malloc.h"
#include <stdio.h>

int main()
{
    int i;
    int j;
    int k;
    char *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char*)ft_malloc(1024);
        printf("adrr : %zu\n", (size_t)addr);
        addr[0] = 42;
        addr[1023] = 42;
        i++;
    }
    show_alloc_mem();
    return (0);
} 
