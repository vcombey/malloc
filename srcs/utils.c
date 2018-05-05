#include "malloc.h"
#include "internal_malloc.h"

void    print_binary(__uint128_t nb) {
    for (int i = 0; i < 128; i++)
    {
        printf("%i", (int)(nb % 2));
        nb >>= 1;
    }
    printf("\n");
}

void	add_chunk_large_zone(struct  chunk_large_zone  **first, struct  chunk_large_zone  *new)
{
    new->next = *first;
    new->prev = NULL;
    if (*first) {
        (*first)->prev = new;
    }
    *first = new;
}

void	del_chunk_large_zone(struct  chunk_large_zone  **first, struct  chunk_large_zone  *node)
{
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;

    if (node == *first)
        *first = node->next;
}
