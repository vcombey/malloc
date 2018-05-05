#include "malloc.h"

int main()
{
    int i;
    char *addr;
    char *tab[129];

    i = 0;
    while (i < 129)
    {
        tab[i] = (char*)ft_malloc(1024);
        i++;
    }
    i = 0;
        show_alloc_mem();
    while (i < 129)
    {
        ft_free(tab[i]);
        i++;
    }
}
