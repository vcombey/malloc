#include "malloc.h"

int main()
{
    int i;
    char *addr;
    char *tab[129];

    i = 0;
    while (i < 129)
    {
        tab[i] = (char*)malloc(1024);
        i++;
    }
    i = 0;
	show_alloc_mem();
    while (i < 129)
    {
        free(tab[i]);
        i++;
    }
	show_alloc_mem();
}
