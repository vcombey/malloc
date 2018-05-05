#include "malloc.h"
#include "internal_malloc.h"

void    show_alloc_chunk(void *ptr, enum e_zone_type zone_type, size_t *i)
{
    struct chunk *c = (struct chunk *)((size_t)ptr + get_offset_zone_header(zone_type) + *i * get_zone_block(zone_type));
    size_t inf = (size_t)c + sizeof(*c);
    size_t sup = (size_t)c + c->size_block * get_zone_block(zone_type);
    printf("%#zx - %#zx: %zu octets\n", inf, sup, sup - inf);
    *i += c->size_block;
}

void    show_alloc_zone(struct zone_reference zone_ref, enum e_zone_type zone_type)
{
    size_t i = 0;
    __uint128_t bitmask;

    while (i < 128)
    {
        bitmask = 1; 
        bitmask <<= i;
        if (zone_ref.allocated_chunks & bitmask)
            show_alloc_chunk(zone_ref.ptr, zone_type, &i);
        else
            i++;
    }
}

struct  zone_reference  find_minimum_addr(struct priority_queue pq, struct  zone_reference previous_min)
{
    size_t i = 0;
    struct  zone_reference new_min = {.allocated_chunks=0, .free_space=0 , .ptr=NULL};

    while (i < pq.lenght)
    {
        if ((new_min.ptr == NULL || pq.vec[i].ptr < new_min.ptr) && pq.vec[i].ptr > previous_min.ptr)
        {
            new_min = pq.vec[i];
        }
        i++;
    }
    return new_min;
}

void    show_alloc_priority_queue(struct priority_queue pq, enum e_zone_type zone_type)
{
    size_t i = 0;
    struct  zone_reference min = {.allocated_chunks=0, .free_space=0 , .ptr=NULL};

    while (i < pq.lenght)
    {
        min = find_minimum_addr(pq, min);
        show_alloc_zone(min, zone_type);
        printf("\n");
        i++;
    }
}

struct  chunk_large_zone  *find_min_large_zone(struct chunk_large_zone  *first, void *previous_min)
{
    void    *new_min = NULL;
    struct  chunk_large_zone  *tmp = first;

    while (tmp)
    {
        if ((new_min == NULL || (size_t)tmp < (size_t)new_min) && (size_t)tmp > (size_t)previous_min)
        {
            new_min = tmp;
        }
        tmp = tmp->next;
    }
    return new_min;
}

void    show_alloc_large_zone(struct  chunk_large_zone  *large_zone_first)
{
    size_t                      len = len_chunk_large_zone(large_zone_first);
    size_t                      i = 0;
    struct  chunk_large_zone    *min = NULL;

    while (i < len)
    {
        min = find_min_large_zone(large_zone_first, min);
        printf("%#zx - %#zx: %zu octets\n", (size_t)min + sizeof(*min), (size_t)min + (min->data.size_block / g_zones.page_size + 1) * g_zones.page_size, min->size_octet);
        i++;
    }
}

void show_alloc_mem(void)
{
    printf("TINY: \n");
    show_alloc_priority_queue(g_zones.little_heap, LITTLE);
    printf("SMALL: \n");
    show_alloc_priority_queue(g_zones.medium_heap, MEDIUM);
    printf("LARGE: \n");
    show_alloc_large_zone(g_zones.large_zone_first);
}
