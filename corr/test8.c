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
        addr = (char*)malloc(1024);
		free(addr + 8);
        addr[0] = 42;
        addr[1023] = 42;
        i++;
    }
    return (0);
} 