/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:54:29 by vcombey           #+#    #+#             */
/*   Updated: 2018/05/20 14:06:11 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"

enum e_zone_type	zone_type_from_size(size_t size)
{
	if (size <= LITTLE_MAX)
		return (LITTLE);
	if (size > LITTLE_MAX && size <= MEDIUM_MAX)
		return (MEDIUM);
	if (size > MEDIUM_MAX)
		return (LARGE);
	return (-1);
}

size_t				zone_size_from_zone_type(enum e_zone_type zone_type)
{
	if (zone_type == LITTLE)
		return (LITTLE_ZONE_SIZE);
	else if (zone_type == MEDIUM)
		return (MEDIUM_ZONE_SIZE);
	return (-1);
}

size_t				zone_block_from_zone_type(enum e_zone_type zone_type)
{
	if (zone_type == LITTLE)
		return (LITTLE_BLOCK);
	else if (zone_type == MEDIUM)
		return (MEDIUM_BLOCK);
	return (-1);
}

size_t				size_block_from_size(size_t size)
{
	return ((size + sizeof(struct s_chunk)) / \
		zone_block_from_zone_type(zone_type_from_size(size)) + 1);
}

size_t				bitmask_from_size_block(size_t size_block)
{
	__uint128_t	bitmask;

	bitmask = 0;
	while (size_block > 0)
	{
		bitmask <<= 1;
		bitmask += 1;
		size_block--;
	}
	return (bitmask);
}
