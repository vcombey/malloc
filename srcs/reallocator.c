#include "malloc.h"
#include "internal_malloc.h"
#include <string.h>

void	*realloc_another_place(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr = malloc(new_size);
	printf("old size %zu new_size%zu \n", old_size, new_size);
	size_t min_size = old_size < new_size ? old_size : new_size;
	memcpy(new_ptr, ptr, min_size);
	free(ptr);
	return (new_ptr);
}

void	*realloc_large_zone(void *ptr, size_t size)
{
	struct chunk_large_zone	*node;
	
	node = ((struct chunk_large_zone *)ptr) - 1;
	if (node->data.size_block / g_zones.page_size >= size / g_zones.page_size)
		return (ptr);
	return realloc_another_place(ptr, node->size_octet, size);
}

void	*realloc_zone(struct priority_queue *pq, void *ptr, struct chunk *chunk, size_t size)
{
	size_t					new_size_block;
	struct zone_reference	*zone_ref;
	__uint128_t				bitmask;
	__uint128_t				new_bitmask;

	enum e_zone_type new_zone_type = get_zone_type_from_size(size);
	//TODO:chunk->size_block * get_zone_block(chunk->zone_type) - sizeof
	//structchunk
	if (new_zone_type != chunk->zone_type)
		return realloc_another_place(ptr, chunk->size_block * get_zone_block(chunk->zone_type) - sizeof(struct chunk), size);
	new_size_block = get_nb_block_from_size(size, chunk->zone_type);
	if ((zone_ref = get_zone_ref(chunk)) == NULL)
		return NULL;
	bitmask = size_block_bitmask(chunk->size_block);
	new_bitmask = size_block_bitmask(new_size_block);
	if (new_bitmask <= bitmask)
	{
		zone_ref->allocated_chunks ^= (bitmask << chunk->offset_block ^ \
				new_bitmask << chunk->offset_block);
		zone_ref->free_space -= new_size_block - chunk->size_block;
		chunk->size_block = new_size_block;
		sift_up(pq, zone_ref - pq->vec);
		return (ptr);
	}
	if ((new_bitmask > bitmask) &&\
			(((zone_ref->allocated_chunks & ((bitmask ^ new_bitmask)\
						<< chunk->offset_block)) == 0)\
				&& chunk->offset_block + new_size_block <= 128))
	{
		zone_ref->allocated_chunks |= new_bitmask << chunk->offset_block;
		zone_ref->free_space -= new_size_block - chunk->size_block;
		chunk->size_block = new_size_block;
		sift_down(pq, zone_ref - pq->vec);
		return (ptr);
	}
	return realloc_another_place(ptr, chunk->size_block * get_zone_block(chunk->zone_type) - sizeof(struct chunk), size);
}

void	*reallocator(void *ptr, size_t size)
{
	struct chunk	*chunk_cast = ((struct chunk *)ptr) - 1;

	printf("reallocator\n");
#ifndef UNSAFE_ALLOC
	if (!pointer_belong_to_us(((struct chunk *)ptr) - 1))
	{
		printf("pointer being reallocated was not allocated\n");
		return NULL;
	}
#endif
	if (chunk_cast->is_free)
	{
		printf("double free\n");
		return NULL;
	}
	printf("pointer being reallocated was allocated\n");
	if (chunk_cast->zone_type == LARGE)
		return realloc_large_zone(ptr, size);
	else if (chunk_cast->zone_type == LITTLE)
		return realloc_zone(&g_zones.little_heap, ptr, chunk_cast, size);
	else if (chunk_cast->zone_type == MEDIUM)
		return realloc_zone(&g_zones.medium_heap, ptr, chunk_cast, size);
	return (NULL);
}
