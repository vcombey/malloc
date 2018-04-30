#include "malloc.h"
#include "internal_malloc.h"

void    unimplemented(char *mess)
{
    printf("%s", mess);
    exit(1);
}

void    swap_nodes(struct priority_queue *a, struct priority_queue *b)
{
    struct priority_queue tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void    sift_up(struct priority_queue *pq, size_t pos)
{
    while (pos > 0 && pq->vec[pos].free_space > pq->vec[pos / 2].free_space) {
        swap_nodes(&pq[pos], &pq[pos / 2]);
        pos /= 2;
    }
}

int    add_priority_queue(struct priority_queue *pq, struct zone_reference new_node)
{
    if (pq->lenght == pq->size)
    {
        void *new_vec;
        if ((new_vec = mmap(pq->vec, pq->size + g_zones.size_block, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
            return -1;
        memove(new_vec, pq->vec, pq->size);
        pq->size += g_zones.size_block;
        pq->vec = new_vec;
    }
    ((struct chunk *)new_node->ptr)->offset_zone_ref = pq->lenght;
    pq->vec[pq->lenght] = new_node;
    sift_up(pq, pq->lenght);
    pq->lenght += 1;
    return 0;
}

/*void    del_priority_queue(struct priority_queue *pq)*/
