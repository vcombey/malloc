/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_reference.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:54:29 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/03 20:33:29 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"

int					new_zone_reference(enum e_zone_type zone_type,\
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
	new_zone_ref->free_space = NB_BLOCK_ZONE;
	return (0);
}

void				del_zone_reference(enum e_zone_type zone_type,\
		struct s_zone_ref *new_zone_ref)
{
	munmap(new_zone_ref,
		zone_size_from_zone_type(zone_type));
}

struct s_zone_ref	*zone_ref_from_chunk(struct s_chunk *chunk)
{
	struct s_header_zone	*header;

	header = (struct s_header_zone *)((size_t)chunk -\
			chunk->offset_block * zone_block_from_zone_type(chunk->zone_type)\
			- offset_zone_header(chunk->zone_type));
	if (!check_header(header))
		panic("bad header magic");
	if (!pointer_belong_to_us((void *)header))
		return (NULL);
	return (header->parent);
}

size_t				offset_zone_header(enum e_zone_type zone_type)
{
	if (zone_type == LITTLE)
		return (LITTLE_HEADER_SIZE);
	else if (zone_type == MEDIUM)
		return (MEDIUM_HEADER_SIZE);
	return (-1);
}

int					offset_place_chunk(__uint128_t allocated_chunks,\
		size_t size_block,
		__uint128_t bitmask)
{
	int		i;

	i = 0;
	while (i <= NB_BLOCK_ZONE - (int)size_block)
	{
		if ((bitmask & allocated_chunks) == 0)
			return (i);
		bitmask <<= 1;
		i++;
	}
	return (-1);
}
