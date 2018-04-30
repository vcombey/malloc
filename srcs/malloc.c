#include "malloc.h"
#include "internal_malloc.h"

struct zones g_zones;

void    constructor(struct zones *z)
{
    z->init = true;
    z->page_size = getpagesize();
}

size_t  size_block_bitmask(size_t size_block)
{
    
    __uint128_t   bitmask = 0;

    while (size_block > 0)
    {
        bitmask <<= 1;
        bitmask += 1;
        size_block--;
    }
    return bitmask;
}

int     offset_place_chunk(__uint128_t  allocated_chunks, size_t size_block, __uint128_t bitmask)
{
    int         i = 0;

    while (i < 128 - (int)size_block)
    {
        if ((bitmask & allocated_chunks) == 0)
            return i;
        bitmask <<= 1;
        i++;
    }
    return -1;
}

/* return the addr for the user */
void    *try_add_chunk_zone_reference(struct zone_reference *zone_ref, size_t size_block, enum e_zone_type zone_type)
{
    __uint128_t bitmask = size_block_bitmask(size_block);
    int offset;

    if ((offset = offset_place_chunk(zone_ref->allocated_chunks, size_block, bitmask)) == -1)
    {
        return NULL;
    }
    zone_ref->allocated_chunks &= bitmask << offset;
    zone_ref->free_space -= size_block;
    struct chunk *chunk_cast = (struct chunk *)((size_t)zone_ref->ptr + offset * get_zone_block(zone_type));
    chunk_cast->size_block = size_block;
    return chunk_cast + 1;
}

void    *move_another_place(struct  priority_queue *pq, size_t size_block, enum e_zone_type zone_type)
{
    void *addr;
    struct zone_reference new_zone_ref;

    if (new_zone_reference(zone_type, &new_zone_ref) == -1)
        return NULL;
    addr = try_add_chunk_zone_reference(&new_zone_ref, size_block, zone_type);
    add_priority_queue(pq, new_zone_ref);
    return addr;
}

void    *allocator_in_zone(struct  priority_queue *pq, size_t size_block, enum e_zone_type zone_type)
{
    void *addr;

    if (pq->lenght != 0 && pq->vec[0].free_space > size_block)
    {
        if ((addr = try_add_chunk_zone_reference(&pq->vec[0], size_block, zone_type)) == NULL)
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
    if (size <= LITTLE_MAX) {
        // TODO: see the + 1
        return allocator_in_zone(&z->little_heap, size / get_zone_block(LITTLE) + 1, LITTLE);
    }
    if (size > LITTLE_MAX && size <= MEDIUM_MAX) {
        return allocator_in_zone(&z->medium_heap, size / get_zone_block(MEDIUM) + 1, MEDIUM);
    }
    if (size > MEDIUM_MAX) {
        unimplemented("large zone unimplemented");
        return NULL;
    }
    return NULL;
}

void    *ft_malloc(size_t size)
{
    ft_putstr_fd("malloc\n", 2);

    size += 16;
    if (size <= 0)
        return NULL;
    if (!g_zones.init)
    {
        constructor(&g_zones);
    }
    return allocator(&g_zones, size);
}
