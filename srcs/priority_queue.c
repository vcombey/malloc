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

void    add_priority_queue(struct priority_queue *pq, struct zone_reference new)
{
    if (pq->lenght == pq->size) {
        unimplemented("out of size priority queue");
    }
    pq->vec[pq->lenght] = new;
    sift_up(pq, pq->lenght);
    pq->lenght += 1;
}

/*void    del_priority_queue(struct priority_queue *pq)*/
