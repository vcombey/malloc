/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocator.next.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:54:29 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/16 20:07:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"
#include <string.h>

static void	*realloc_another_place(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	min_size;

	new_ptr = allocator(&g_zones, new_size);
	min_size = old_size < new_size ? old_size : new_size;
	ft_memcpy(new_ptr, ptr, min_size);
	desalocator(ptr);
	return (new_ptr);
}

void		*realloc_large_zone(void *ptr, size_t size)
{
	struct s_chunk_large_zone	*node;

	node = ((struct s_chunk_large_zone *)ptr) - 1;
	if (node->data.size_block / g_zones.page_size >= size / g_zones.page_size)
		return (ptr);
	return (realloc_another_place(ptr, node->size_octet, size));
}

static void	*realloc_greater(void *ptr, struct s_zone_ref *zone_ref, \
		struct s_chunk *chunk, size_t new_size_block)
{
	__uint128_t				bitmask;
	__uint128_t				new_bitmask;
	struct s_heap			*pq;

	pq = get_heap(&g_zones, chunk->zone_type);
	bitmask = bitmask_from_size_block(chunk->size_block);
	new_bitmask = bitmask_from_size_block(new_size_block);
	zone_ref->allocated_chunks |= new_bitmask << chunk->offset_block;
	zone_ref->free_space -= new_size_block - chunk->size_block;
	chunk->size_block = new_size_block;
	sift_down(get_heap(&g_zones, chunk->zone_type), zone_ref - pq->vec);
	return (ptr);
}

static void	*realloc_lower(void *ptr, struct s_zone_ref *zone_ref, \
		struct s_chunk *chunk, size_t new_size_block)
{
	__uint128_t				bitmask;
	__uint128_t				new_bitmask;
	struct s_heap			*pq;

	pq = get_heap(&g_zones, chunk->zone_type);
	bitmask = bitmask_from_size_block(chunk->size_block);
	new_bitmask = bitmask_from_size_block(new_size_block);
	zone_ref->allocated_chunks ^= (bitmask << chunk->offset_block ^ \
			new_bitmask << chunk->offset_block);
	zone_ref->free_space -= new_size_block - chunk->size_block;
	chunk->size_block = new_size_block;
	sift_up(pq, zone_ref - pq->vec);
	return (ptr);
}

void		*realloc_zone(void *ptr, struct s_chunk *chunk, size_t size)
{
	size_t					new_size_block;
	struct s_zone_ref		*zone_ref;
	__uint128_t				bitmask;
	__uint128_t				new_bitmask;

	if (zone_type_from_size(size) != chunk->zone_type)
		return (realloc_another_place(ptr, chunk->size_block * \
zone_block_from_zone_type(chunk->zone_type) - sizeof(struct s_chunk), size));
		new_size_block = size_block_from_size(size);
	if ((zone_ref = zone_ref_from_chunk(chunk)) == NULL)
		return (NULL);
	bitmask = bitmask_from_size_block(chunk->size_block);
	new_bitmask = bitmask_from_size_block(new_size_block);
	if (new_size_block <= chunk->size_block)
		return (realloc_lower(ptr, zone_ref, chunk, new_size_block));
	if ((new_bitmask > bitmask) &&\
			(((zone_ref->allocated_chunks & ((bitmask ^ new_bitmask)\
						<< chunk->offset_block)) == 0)\
			&& chunk->offset_block + new_size_block <= NB_BLOCK_ZONE))
		return (realloc_greater(ptr, zone_ref, chunk, new_size_block));
	return ((realloc_another_place(ptr, chunk->size_block * \
					zone_block_from_zone_type(chunk->zone_type) \
					- sizeof(struct s_chunk), size)));
}
