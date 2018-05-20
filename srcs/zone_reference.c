#include "malloc.h"
#include "internal_malloc.h"

int		new_zone_reference(enum e_zone_type zone_type,\
		struct s_zone_ref *new_zone_ref)
{
	void	*addr;

	if ((addr = mmap(NULL,
					zone_size_from_zone_type(zone_type),
					PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))
			== MAP_FAILED)
		return (-1);
	new_zone_ref->ptr = addr;
	new_zone_ref->ptr->parent = NULL;
	new_zone_ref->ptr->magic = MAGIC;
	new_zone_ref->allocated_chunks = 0;
	new_zone_ref->free_space = 128;
	return (0);
}

struct s_zone_ref	*zone_ref_from_chunk(struct s_chunk *chunk)
{
    struct s_header_zone      *header;

	header = (struct s_header_zone *)((size_t)chunk -\
            chunk->offset_block * zone_block_from_zone_type(chunk->zone_type)\
            - offset_zone_header(chunk->zone_type));
	if (!check_header(header))
		panic("bad header magic");
#ifndef UNSAFE_ALLOC
	if (!pointer_belong_to_us((void *)header))
	{
		printf("header doesnt belong to us");
		return NULL;
	}
#endif
	return (header->parent);
}

size_t	offset_zone_header(enum e_zone_type zone_type)
{
	if (zone_type == LITTLE)
		return (LITTLE_HEADER_SIZE);
	else if (zone_type == MEDIUM)
		return (MEDIUM_HEADER_SIZE);
	return (-1);
}

int		offset_place_chunk(__uint128_t allocated_chunks,\
		size_t size_block,
		__uint128_t bitmask)
{
	int		i;

	i = 0;
	while (i <= 128 - (int)size_block)
	{
		if ((bitmask & allocated_chunks) == 0)
			return (i);
		bitmask <<= 1;
		i++;
	}
	return (-1);
}

bool	pointer_belong_to_us(void *ptr)
{
	if (is_in_chunk_large_zone(((struct s_chunk_large_zone *)ptr) - 1, g_zones.large_zone_first) ||
			(is_in_heap(&g_zones.little_heap, ((struct s_chunk *)ptr), LITTLE)) ||
			(is_in_heap(&g_zones.medium_heap, ((struct s_chunk *)ptr), MEDIUM)))
	{
	//	printf("pointer belong to us\n");
		return true;
	}
	return false;
}

bool	check_header(struct s_header_zone *header)
{
	return (header->magic == MAGIC);
}
