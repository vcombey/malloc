#include "malloc.h"
#include "internal_malloc.h"

void	desalocator(void *ptr)
{
	struct chunk *chunk_cast = ((struct chunk *)ptr) - 1;
	if (chunk_cast->zone_type == LARGE)
	{
		struct chunk_large_zone *node = ((struct chunk_large_zone *)ptr) - 1;
		del_chunk_large_zone(&g_zones.large_zone_first, node);
		if (munmap(node, node->size_octet) == -1)
			perror("munmap failed");
		return ;
	}
	struct header_zone *header = (struct header_zone *)((size_t)chunk_cast - chunk_cast->offset_block * get_zone_block(chunk_cast->zone_type) - get_offset_zone_header(chunk_cast->zone_type));
	struct zone_reference *zone_ref = header->parent;
	__uint128_t bitmask = size_block_bitmask(chunk_cast->size_block);
	zone_ref->allocated_chunks ^= bitmask << chunk_cast->offset_block;
	zone_ref->free_space += chunk_cast->size_block;
	if (chunk_cast->zone_type == LITTLE)
		update_priority_queue(&g_zones.little_heap, zone_ref, LITTLE);
	if (chunk_cast->zone_type == MEDIUM)
		update_priority_queue(&g_zones.medium_heap, zone_ref, MEDIUM);
}
