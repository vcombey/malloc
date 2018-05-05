#include "malloc.h"
#include "internal_malloc.h"
#include <string.h>

struct zones g_zones;

void    constructor(struct zones *z)
{
    z->init = true;
    z->page_size = getpagesize();
}

void    *ft_malloc(size_t size)
{
    if (size <= 0)
        return NULL;
    if (!g_zones.init)
        constructor(&g_zones);
    void *addr = allocator(&g_zones, size);
    return addr;
}

void ft_free(void *ptr)
{
    if (ptr == NULL || (size_t)ptr % 8 != 0)
        return ;
    struct chunk *chunk_cast = ((struct chunk *)ptr) - 1;
    if (chunk_cast->zone_type == LARGE)
    {
        struct chunk_large_zone *node = ((struct chunk_large_zone *)ptr) - 1;
        del_chunk_large_zone(&g_zones.large_zone_first, node);
        if (munmap(node, node->size_octet) == -1)
            perror("munmap failed");
        return ;
    }
    struct  header_zone *header = (struct header_zone *)((size_t)chunk_cast - chunk_cast->offset_block * get_zone_block(chunk_cast->zone_type) - get_offset_zone_header(chunk_cast->zone_type));
    struct zone_reference *zone_ref = header->parent;
    __uint128_t bitmask = size_block_bitmask(chunk_cast->size_block);
    zone_ref->allocated_chunks ^= bitmask << chunk_cast->offset_block;
    zone_ref->free_space += chunk_cast->size_block;

    if (chunk_cast->zone_type == LITTLE)
        update_priority_queue(&g_zones.little_heap, zone_ref, LITTLE);
    if (chunk_cast->zone_type == MEDIUM)
        update_priority_queue(&g_zones.medium_heap, zone_ref, MEDIUM);
}

void *ft_realloc(void *ptr, size_t size)
{
    if (ptr == NULL || (size_t)ptr % 8 != 0)
    {
        return NULL;
    }
    struct chunk *chunk_cast = ((struct chunk *)ptr) - 1;
    if (chunk_cast->zone_type == LARGE) {
        struct chunk_large_zone *node = ((struct chunk_large_zone *)ptr) - 1;
        if (node->data.size_block / g_zones.page_size >= size / g_zones.page_size)
            return ptr;
        void *new_ptr = malloc(size);
        memcpy(new_ptr, ptr, node->size_octet);
        ft_free(ptr);
        return (new_ptr);
    }
    size_t size_block = size / get_zone_block(chunk_cast->zone_type) + 1;
    struct  header_zone *header = (struct header_zone *)((size_t)chunk_cast - chunk_cast->offset_block * get_zone_block(chunk_cast->zone_type) - get_offset_zone_header(chunk_cast->zone_type));
    struct zone_reference *zone_ref = header->parent;
    
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
