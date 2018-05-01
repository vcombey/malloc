#include "malloc.h"
#include "internal_malloc.h"

void    unimplemented(char *mess)
{
    printf("%s", mess);
    exit(1);
}

void    swap_nodes(struct zone_reference *a, struct zone_reference *b)
{
    struct zone_reference tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
    a->ptr->parent = a;
    b->ptr->parent = b;
}

void    sift_up(struct priority_queue *pq, size_t pos)
{
    while (pos > 0 && pq->vec[pos].free_space > pq->vec[pos / 2].free_space)
    {
        swap_nodes(&pq->vec[pos], &pq->vec[pos / 2]);
        pos /= 2;
    }
}

void    recalc_header_zone(struct  priority_queue *new_vec, size_t size)
{
    size_t i = 0;

    while (i < size)
    {
        new_vec->vec[i].ptr->parent = &new_vec->vec[i];
        i++;
    }
}

#include <string.h>
int    add_priority_queue(struct priority_queue *pq, struct zone_reference new_node)
{
    if (pq->lenght == pq->size)
    {
        void *new_vec;
        if ((new_vec = mmap(pq->vec, pq->size * sizeof(*pq->vec) + g_zones.page_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
            return -1;
        memmove(new_vec, pq->vec, pq->size);
        recalc_header_zone(new_vec, pq->size);
        munmap(pq->vec, pq->size * sizeof(*pq->vec));
        pq->size += g_zones.page_size / sizeof(*pq->vec);
        pq->vec = new_vec;
    }
    new_node.ptr->parent = &pq->vec[pq->lenght];
    pq->vec[pq->lenght] = new_node;
    sift_up(pq, pq->lenght);
    pq->lenght += 1;
    return 0;
}

/*void    del_priority_queue(struct priority_queue *pq)*/
