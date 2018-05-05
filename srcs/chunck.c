#include "malloc.h"
#include "internal_malloc.h"

void    show_alloc_chunk(void *ptr, enum e_zone_type zone_type, int *i)
{
    struct chunk *c = (struct chunk *)((size_t)ptr + get_offset_zone_header(zone_type) + *i * get_zone_block(zone_type));
    size_t inf = (size_t)c + sizeof(*c);
    size_t sup = (size_t)c + c->size_block * get_zone_block(zone_type);
    printf("%#zx - %#zx: %zu\n", inf, sup, sup - inf);
    *i += c->size_block;
}
