#include "malloc.h"
#include "internal_malloc.h"

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

