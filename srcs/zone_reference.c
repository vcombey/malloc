#include "malloc.h"
#include "internal_malloc.h"

size_t  get_zone_size(enum e_zone_type zone_type)
{
    if (zone_type == LITTLE) {
        return LITTLE_ZONE_SIZE;
    }
    else if (zone_type == MEDIUM) {
        return MEDIUM_ZONE_SIZE;
    }
    return -1; 
}

size_t  get_zone_block(enum e_zone_type zone_type)
{
    if (zone_type == LITTLE) {
        return LITTLE_BLOCK;
    }
    else if (zone_type == MEDIUM) {
        return MEDIUM_BLOCK;
    }
    return -1; 
}

size_t  get_offset_zone_header(enum e_zone_type zone_type)
{
    if (zone_type == LITTLE) {
        return LITTLE_HEADER_SIZE;
    }
    else if (zone_type == MEDIUM) {
        return MEDIUM_HEADER_SIZE;
    }
    return -1; 
}
int     new_zone_reference(enum e_zone_type zone_type, struct zone_reference *new_zone_ref)
{
    void                *addr;

    if ((addr = mmap(NULL, get_zone_size(zone_type), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
        return -1;
    new_zone_ref->ptr = addr;
    new_zone_ref->allocated_chunks = 0;
    new_zone_ref->free_space = 128;
    return 0;
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

    while (i <= 128 - (int)size_block)
    {
        if ((bitmask & allocated_chunks) == 0)
            return i;
        bitmask <<= 1;
        i++;
    }
    return -1;
}

void    show_alloc_zone(struct zone_reference zone_ref, enum e_zone_type zone_type)
{
    int i = 0;

    while (i < 128)
    {
        if (zone_ref.allocated_chunks & (1 << i))
            show_alloc_chunk(zone_ref.ptr, zone_type, &i);
        else
            i++;
    }
}












