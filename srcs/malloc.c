#include "malloc.h"
#include "internal_malloc.h"

struct zones g_zones;

void    constructor(struct zones *z)
{
    printf("constructor \n");
    z->init = true;
    z->page_size = getpagesize();
}

/* return the addr for the user */
void    *try_add_chunk_zone_reference(struct zone_reference *zone_ref, size_t size_block, enum e_zone_type zone_type)
{
    __uint128_t bitmask = size_block_bitmask(size_block);
    print_binary(bitmask);
    int offset;

    if ((offset = offset_place_chunk(zone_ref->allocated_chunks, size_block, bitmask)) == -1)
    {
        printf("can t allocate in this zone reference\n");
        return NULL;
    }
    printf("offset %i \n", offset);
    printf("allocated chunks ");
    print_binary(zone_ref->allocated_chunks);
    printf("bitmask << offset ");
    print_binary(bitmask << offset);
    zone_ref->allocated_chunks |= bitmask << offset;
    printf("allocated chunks ");
    print_binary(zone_ref->allocated_chunks);
    zone_ref->free_space -= size_block;
    printf("free space %i \n", zone_ref->free_space);
    printf("zone ref %#zx \n", (size_t)zone_ref->ptr);
    struct chunk *chunk_cast = (struct chunk *)((size_t)zone_ref->ptr + get_offset_zone_header(zone_type) + offset * get_zone_block(zone_type));
    printf("chunk addr %#zx \n", (size_t)chunk_cast);
    chunk_cast->size_block = size_block;
    //WARN
    chunk_cast->offset_block = offset;
    chunk_cast->zone_type = zone_type;
    return chunk_cast + 1;
}

void    *move_another_place(struct  priority_queue *pq, size_t size_block, enum e_zone_type zone_type)
{
    void *addr;
    struct zone_reference new_zone_ref;

    if (new_zone_reference(zone_type, &new_zone_ref) == -1)
        return NULL;
    addr = try_add_chunk_zone_reference(&new_zone_ref, size_block, zone_type);
    //TODO: free the zone
    if (add_priority_queue(pq, new_zone_ref) == -1)
        return NULL;
    return addr;
}

void    *allocator_in_zone(struct  priority_queue *pq, size_t size_block, enum e_zone_type zone_type)
{
    void *addr;

    if (pq->lenght != 0 && pq->vec[0].free_space >= size_block)
    {
        if ((addr = try_add_chunk_zone_reference(&pq->vec[0], size_block, zone_type)) == NULL)
        {
            printf("root is filled, move another place \n");
             return move_another_place(pq, size_block, zone_type);
        }
        sift_down(pq, 0);
        return addr;
    }
    else
    {
        printf("priority queue is empty \n");
        return move_another_place(pq, size_block, zone_type);
    }
}

void    *allocator(struct zones *z, size_t size)
{
    if (size <= LITTLE_MAX) {
        printf("allocator little \n");
        // TODO: see the + 1
        return allocator_in_zone(&z->little_heap, size / get_zone_block(LITTLE) + 1, LITTLE);
    }
    if (size > LITTLE_MAX && size <= MEDIUM_MAX) {
        printf("allocator medium \n");
        printf("size in block %lu \n", size / get_zone_block(MEDIUM) + 1);

        return allocator_in_zone(&z->medium_heap, size / get_zone_block(MEDIUM) + 1, MEDIUM);
    }
    if (size > MEDIUM_MAX) {
        unimplemented("large zone unimplemented");
        return NULL;
    }
    unimplemented("cant append");
    return NULL;
}

void    *ft_malloc(size_t size)
{
    printf("malloc\n");


    size += 16;
    if (size <= 0)
        return NULL;
    if (!g_zones.init)
    {
        constructor(&g_zones);
    }
    void *addr = allocator(&g_zones, size);
    printf("---------------\n");
    return addr;
}

void ft_free(void *ptr)
{
    printf("**********************\n");
    if (ptr == NULL)
        return ;
    struct chunk *chunk_cast = ((struct chunk *)ptr) - 1;
    
    struct  header_zone *header = (struct header_zone *)((size_t)chunk_cast - chunk_cast->offset_block * get_zone_block(chunk_cast->zone_type) - get_offset_zone_header(chunk_cast->zone_type));
    struct zone_reference *zone_ref = header->parent;
    printf("zone ref %#zx \n", (size_t)zone_ref->ptr);
    
    __uint128_t bitmask = size_block_bitmask(chunk_cast->size_block);
    printf("allocated chunks ");
    print_binary(zone_ref->allocated_chunks);
    zone_ref->allocated_chunks ^= bitmask << chunk_cast->offset_block;
    printf("allocated chunks ");
    print_binary(zone_ref->allocated_chunks);
    zone_ref->free_space += chunk_cast->size_block;
    printf("**********************\n");


    // TODO:siftup
}

void *ft_realloc(void *ptr, size_t size)
{
    printf("**********************\n");
    if (ptr == NULL) {
        unimplemented("null ptr in realoc");
        return NULL;
    }
    struct chunk *chunk_cast = ((struct chunk *)ptr) - 1;
    size_t size_block = size / get_zone_block(chunk_cast->zone_type) + 1;
    struct  header_zone *header = (struct header_zone *)((size_t)chunk_cast - chunk_cast->offset_block * get_zone_block(chunk_cast->zone_type) - get_offset_zone_header(chunk_cast->zone_type));
    struct zone_reference *zone_ref = header->parent;
    printf("zone ref %#zx \n", (size_t)zone_ref->ptr);
    
    __uint128_t bitmask = size_block_bitmask(chunk_cast->size_block);
    __uint128_t new_bitmask = size_block_bitmask(size_block);
    if (new_bitmask <= bitmask) {
        zone_ref->allocated_chunks ^= (bitmask << chunk_cast->offset_block ^ new_bitmask << chunk_cast->offset_block);
        return ptr;
    }
    if ((new_bitmask > bitmask) &&
        (((zone_ref->allocated_chunks & ((bitmask ^ new_bitmask) << chunk_cast->offset_block)) == 0)
            && chunk_cast->offset_block + size_block <= 128))
    {
        zone_ref->allocated_chunks |= new_bitmask << chunk_cast->offset_block;
        return ptr;
    }
    free(ptr);
    return (malloc(size));
}
