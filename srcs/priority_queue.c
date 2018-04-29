
struct priority_queue {
    size_t                  lenght;
    size_t                  size;
    struct page_reference   *vec;
}

void    unimplemented(char *mess) {
    printf("%s", mess);
    exit(1);
}

void    sift_up(struct priority_queue *pq, size_t pos) {
    while (pos > 0 && pq[pos].nb_free > pq[pos / 2].nb_free
}

void    add_priority_queue(struct priority_queue *pq, struct page_reference new) {
    if (pq->lenght == pq->size) {
        unimplemented("out of size priority queue");
    }
    pq->vec[pq->lenght] = new;
    sift_up(pq, pq->lenght);
    pq->lenght += 1;
}

void    del_priority_queue(struct priority_queue *pq) {

}
