#include "malloc.h"
#include "internal_malloc.h"

void	add_chunk_large_zone(struct chunk_large_zone **first,\
		struct chunk_large_zone *new)
{
	new->next = *first;
	new->prev = NULL;
	if (*first)
	{
		(*first)->prev = new;
	}
	*first = new;
}

void	del_chunk_large_zone(struct chunk_large_zone **first,\
		struct chunk_large_zone *node)
{
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (node == *first)
		*first = node->next;
}

size_t	len_chunk_large_zone(struct chunk_large_zone *first)
{
	size_t	i;

	i = 0;
	while (first)
	{
		first = first->next;
		i++;
	}
	return (i);
}

bool	is_in_chunk_large_zone(struct chunk_large_zone *node, struct chunk_large_zone *first)
{
	while (first)
	{
		if (first == node)
			return true;
		first = first->next;
	}
	return (false);

}

struct zone_reference	*zone_ref_from_chunk(struct chunk *chunk)
{
    struct header_zone      *header;

	header = (struct header_zone *)((size_t)chunk -\
            chunk->offset_block * zone_block_from_zone_type(chunk->zone_type)\
            - offset_zone_header(chunk->zone_type));
	if (!check_header(header))
		panic("bad header magic");
#ifndef UNSAFE_ALLOC
	if (!pointer_belong_to_us((void *)header))
		return NULL;
#endif
	return (header->parent);
}
