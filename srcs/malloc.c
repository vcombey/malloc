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
    printf("offset %i \n", offset);/*{{{*/
    printf("allocated chunks ");
    print_binary(zone_ref->allocated_chunks);
    printf("bitmask << offset ");
    print_binary(bitmask << offset);/*}}}*/
    zone_ref->allocated_chunks |= bitmask << offset;
    printf("allocated chunks ");/*{{{*/
    print_binary(zone_ref->allocated_chunks);/*}}}*/
    zone_ref->free_space -= size_block;
    printf("free space %i \n", zone_ref->free_space);/*{{{*/
    printf("zone ref %#zx \n", (size_t)zone_ref->ptr);/*}}}*/
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
        
void    *allocator_large_zone(struct  chunk_large_zone  **first, size_t size_octet)
{
    struct  chunk_large_zone  *addr;

    if ((addr = mmap(NULL, size_octet + sizeof(struct  chunk_large_zone), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
        return NULL;
    addr->data.zone_type = LARGE;
    addr->data.size_block = size_octet;
    add_chunk_large_zone(first, addr);
    return addr + 1;
}

void    *allocator(struct zones *z, size_t size)
{
    if (size <= LITTLE_MAX) {
        printf("allocator little \n");
        // TODO: see the + 1
        return allocator_in_zone(&z->little_heap, (size + sizeof(struct chunk)) / get_zone_block(LITTLE) + 1, LITTLE);
    }
    if (size > LITTLE_MAX && size <= MEDIUM_MAX) {
        printf("allocator medium \n");
        printf("size in block %lu \n", size / get_zone_block(MEDIUM) + 1);
        return allocator_in_zone(&z->medium_heap, (size  + sizeof(struct chunk))/ get_zone_block(MEDIUM) + 1, MEDIUM);
    }
    if (size > MEDIUM_MAX) {
        return allocator_large_zone(&z->large_zone_first, size);
    }
    unimplemented("cant append");
    return NULL;
}

void    *ft_malloc(size_t size)
{
    printf("malloc\n");

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
    if (chunk_cast->zone_type == LARGE) {
        struct chunk_large_zone *node = ((struct chunk_large_zone *)ptr) - 1;
        del_chunk_large_zone(&g_zones.large_zone_first, node);
        if (munmap(node, node->data.size_block) == -1)
            perror("munmap failed");
        return ;
    }
    struct  header_zone *header = (struct header_zone *)((size_t)chunk_cast - chunk_cast->offset_block * get_zone_block(chunk_cast->zone_type) - get_offset_zone_header(chunk_cast->zone_type));
    struct zone_reference *zone_ref = header->parent;
    printf("zone ref %#zx \n", (size_t)zone_ref->ptr);
    
    __uint128_t bitmask = size_block_bitmask(chunk_cast->size_block);
    printf("allocated chunks ");/*{{{*/
    print_binary(zone_ref->allocated_chunks);/*}}}*/
    zone_ref->allocated_chunks ^= bitmask << chunk_cast->offset_block;
    printf("allocated chunks ");/*{{{*/
    print_binary(zone_ref->allocated_chunks);/*}}}*/
    zone_ref->free_space += chunk_cast->size_block;
    printf("**********************\n");


    // TODO:siftup
}
#include <string.h>
void *ft_realloc(void *ptr, size_t size)
{
    printf("**********************\n");
    if (ptr == NULL) {
        unimplemented("null ptr in realoc");
        return NULL;
    }
    struct chunk *chunk_cast = ((struct chunk *)ptr) - 1;
    if (chunk_cast->zone_type == LARGE) {
        struct chunk_large_zone *node = ((struct chunk_large_zone *)ptr) - 1;
        if (node->data.size_block / g_zones.page_size >= size / g_zones.page_size)
            return ptr;
        void *new_ptr = malloc(size);
        memcpy(new_ptr, ptr, node->data.size_block);
        ft_free(ptr);
        return (new_ptr);
    }
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
    ft_free(ptr);
    return (malloc(size));
}

void    show_alloc_large_zone(struct  chunk_large_zone  *large_zone_first)
{
    struct  chunk_large_zone  *tmp = large_zone_first;

    while (tmp)
    {
        printf("%#zx - %#zx: %hhu octets\n", (size_t)tmp + sizeof(*tmp), (tmp->data.size_block / g_zones.page_size + 1) * g_zones.page_size, tmp->data.size_block);
        tmp = tmp->next;
    }
}

void show_alloc_mem(void) {
    printf("TINY: ");
    show_alloc_priority_queue(g_zones.little_heap, LITTLE);
    printf("SMALL: ");
    show_alloc_priority_queue(g_zones.medium_heap, MEDIUM);
    printf("LARGE: \n");
    show_alloc_large_zone(g_zones.large_zone_first);
}
