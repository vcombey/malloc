#include "malloc.h"
#include <stdio.h>

int main()
{
    int i;
    int j;
    int k;
    char *addr;

    i = 0;
    while (i < 10)
    {
        addr = (char*)ft_malloc(1024);
        printf("---addr %#zx \n", (size_t)addr);
        printf("---------------\n");
        addr[0] = 43;
        addr[1023] = 42;
        i++;
    }
    return (0);
} 
