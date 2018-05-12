#include "malloc.h"
#include "internal_malloc.h"

void    desalocator_large_zone(void *ptr)
{
    struct chunk_large_zone *node;

    node = ((struct chunk_large_zone *)ptr) - 1;
    del_chunk_large_zone(&g_zones.large_zone_first, node);
    if (munmap(node, node->size_octet) == -1)
        perror("munmap failed");
    return ;
}

void    desalocator_zone(struct priority_queue *pq, struct chunk *chunk_cast)
{
    struct zone_reference   *zone_ref;
    __uint128_t             bitmask;

	if ((zone_ref = get_zone_ref(chunk_cast)) == NULL)
		return ;
	bitmask = size_block_bitmask(chunk_cast->size_block);
	zone_ref->allocated_chunks ^= bitmask << chunk_cast->offset_block;
	zone_ref->free_space += chunk_cast->size_block;
    update_priority_queue(pq, zone_ref, chunk_cast->zone_type);
}

void	desalocator(void *ptr)
{
    struct chunk            *chunk_cast;

#ifndef UNSAFE_ALLOC
	if (!pointer_belong_to_us(ptr))
	{
		printf("pointer being freed was not allocated\n");
		return ;
	}
#endif
	printf("pointer being freed was allocated\n");
	chunk_cast = ((struct chunk *)ptr) - 1;
	if (chunk_cast->is_free)
	{
		printf("double free\n");
		return;
	}
	if (chunk_cast->zone_type == LARGE)
        return desalocator_large_zone(ptr);
	else if (chunk_cast->zone_type == LITTLE)
        return desalocator_zone(&g_zones.little_heap, chunk_cast);
	else if (chunk_cast->zone_type == MEDIUM)
        return desalocator_zone(&g_zones.medium_heap, chunk_cast);
}
