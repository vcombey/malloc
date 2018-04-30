#include "malloc.h"

struct zones g_zones;

void    constructor(struct zones *z)
{
    z->init = true;
    z->page_size = getpagesize();
}

size_t  get_zone_size(enum e_zone_type zone_type)
{
    if (zone_type == LITTLE) {
        return LITTLE_ZONE_SIZE;
    }
    else if (zone_type == MEDIUM_ZONE_SIZE) {
        return MEDIUM_ZONE_SIZE;
    }
    return -1; 
}

size_t  get_zone_block(enum e_zone_type zone_type)
{
    if (zone_type == LITTLE) {
        return LITTLE_BLOCK;
    }
    else if (zone_type == MEDIUM_ZONE_SIZE) {
        return MEDIUM_BLOCK;
    }
    return -1; 
}

int     new_zone_reference(enum e_zone_type zone_type, struct zone_reference *new_zone_ref)
{
    void                *addr;

    if ((addr = mmap(NULL, get_zone_size(zone_type), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == -1)
        return -1;
    }
    new_zone_ref->ptr = addr;
    new_zone_ref->allocated_chunks = 0;
    new_zone_ref->free_space = 0;
    return 0;
}

void    *try_add_chunk_zone_reference(struct zone_reference *zone_ref, size_t size_block)
{

}

void    *move_another_place(struct  priority_queue *pq, size_t size_block, enum e_zone_type zone_type)
{
    void *addr;

    struct zone_reference new_zone_ref;
    if (new_zone_ref = new_zone_reference(size_block, zone_type) == -1)
        return NULL;
    addr = try_add_chunk_zone_reference(new_zone_ref, size_block);
    add_priority_queue(pq, new_zone_ref);
}

// get the size in nb zone_type block
void    *allocator_in_zone(struct  priority_queue *pq, size_t size_block, enum e_zone_type zone_type)
{
    void *addr;

    if (pq->length != 0 && pq->vec[0].free_space > size_block)
    {
        if ((addr = try_add_chunk_zone_reference(pq->vec[0], size_block)) == NULL)
             return move_another_place(pq, size_block, zone_type);
        return addr;
    }
    else
    {
        return move_another_place(pq, size_block, zone_type);
    }
}

void    *allocator(struct zones *z, size_t size)
{
    if (size < LITTLE_MAX) {
        // TODO: see the + 1
        return allocator_in_zone(&z->little_heap, size / get_zone_block(LITTLE) + 1, LITTLE);
    }
    if (size > LITTLE_MAX && size < MEDIUM_MAX) {
        return allocator_in_zone(&z->medium_heap, size / get_zone_block(MEDIUM) + 1, MEDIUM);
    }
    if (size > MEDIUM_MAX) {
        unimplemented("large zone unimplemented");
        return NULL;
    }
}

void    *ft_malloc(size_t size)
{
    ft_putstr_fd("malloc\n", 2);


    size += 16;

    if (!g_zones.init)
    {
        constructor(&g_zones);
    }
    void    *addr = mmap(NULL, , PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (mmap == -1) {
        return NULL;
    }

    return NULL;
}
