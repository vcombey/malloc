/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desallocator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:54:29 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/03 19:51:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"

void	desalocator_large_zone(void *ptr)
{
	struct s_chunk_large_zone *node;

	node = ((struct s_chunk_large_zone *)ptr) - 1;
	del_chunk_large_zone(&g_zones.large_zone_first, node);
	if (munmap(node, node->size_octet) == -1)
		perror("munmap failed");
	return ;
}

void	desalocator_zone(struct s_heap *pq, struct s_chunk *chunk)
{
	struct s_zone_ref		*zone_ref;
	__uint128_t				bitmask;

	if ((zone_ref = zone_ref_from_chunk(chunk)) == NULL)
		return ;
	bitmask = bitmask_from_size_block(chunk->size_block);
	zone_ref->allocated_chunks ^= bitmask << chunk->offset_block;
	zone_ref->free_space += chunk->size_block;
	update_heap(pq, zone_ref, chunk->zone_type);
}

void	desalocator(void *ptr)
{
	struct s_chunk		*chunk;

	if (ptr == NULL)
		return ;
	if ((size_t)ptr % 16 != 0 || !pointer_belong_to_us(ptr))
	{
		ft_printf("pointer being freed was not allocated\n");
		return ;
	}
	chunk = ((struct s_chunk *)ptr) - 1;
	if (chunk->is_free)
	{
		ft_printf("double free\n");
		return ;
	}
	chunk->is_free = true;
	if (chunk->zone_type == LARGE)
		return (desalocator_large_zone(ptr));
	else if (chunk->zone_type == LITTLE)
		return (desalocator_zone(&g_zones.little_heap, chunk));
	else if (chunk->zone_type == MEDIUM)
		return (desalocator_zone(&g_zones.medium_heap, chunk));
}
