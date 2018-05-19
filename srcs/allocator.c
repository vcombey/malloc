#include "malloc.h"
#include "internal_malloc.h"

void	*try_add_chunk_zone_reference(struct s_zone_ref *zone_ref,\
		size_t size_block,\
		enum e_zone_type zone_type)
{
	__uint128_t		bitmask;
	int				offset;
	struct s_chunk	*chunk;

	bitmask = bitmask_from_size_block(size_block);
	if ((offset = offset_place_chunk(zone_ref->allocated_chunks, size_block, bitmask)) == -1)
		return (NULL);
	zone_ref->allocated_chunks |= bitmask << offset;
	zone_ref->free_space -= size_block;
	chunk = (struct s_chunk *)((size_t)zone_ref->ptr +\
			offset_zone_header(zone_type) +\
			offset * zone_block_from_zone_type(zone_type));
	chunk->size_block = size_block;
	chunk->offset_block = offset;
	chunk->zone_type = zone_type;
	chunk->is_free = false;
	return (chunk + 1);
}

void	*move_another_place(struct s_heap *pq,\
		size_t size_block,\
		enum e_zone_type zone_type)
{
	void					*addr;
	struct s_zone_ref	new_zone_ref;

	if (new_zone_reference(zone_type, &new_zone_ref) == -1)
		return (NULL);
	addr = try_add_chunk_zone_reference(&new_zone_ref, size_block, zone_type);
	//TODO: free the zone
	if (add_heap(pq, new_zone_ref) == -1)
		return (NULL);
	return (addr);
}

void	*allocator_in_zone(struct s_heap *pq,\
		size_t size_block,\
		enum e_zone_type zone_type)
{
	void	*addr;

	if (pq->lenght != 0 && pq->vec[0].free_space >= size_block)
	{
		if ((addr = try_add_chunk_zone_reference(&pq->vec[0],\
						size_block, zone_type)) == NULL)
			return (move_another_place(pq, size_block, zone_type));
		sift_down(pq, 0);
		return (addr);
	}
	else
		return (move_another_place(pq, size_block, zone_type));
}

void	*allocator_large_zone(struct s_chunk_large_zone **first,\
		size_t size_octet)
{
	struct s_chunk_large_zone		*addr;

	if ((addr = mmap(NULL,\
					size_octet + sizeof(struct s_chunk_large_zone),\
					PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,\
					-1, 0)) == MAP_FAILED)
		return (NULL);
	addr->data.zone_type = LARGE;
	addr->size_octet = size_octet;
	add_chunk_large_zone(first, addr);
	return (addr + 1);
}

void	*allocator(struct s_zones *z, size_t size)
{
	// TODO: see the + 1
	enum e_zone_type	zone_type = zone_type_from_size(size);
	if (zone_type == LARGE)
		return (allocator_large_zone(&z->large_zone_first, size));
	return (allocator_in_zone(get_heap(z,zone_type), size_block_from_size(size, zone_type), zone_type));
}
