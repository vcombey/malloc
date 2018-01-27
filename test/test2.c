#include "malloc.h"

int main()
{
    int i;
    char *addr;

    i = 0;
    while (i < 1024)
    {
        addr = (char*)ft_malloc(1024);
        addr[0] = 42;
        ft_free(addr);
        show_alloc_mem();
        i++;
    }
    return (0);
} 
