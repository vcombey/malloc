/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:57:10 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/03 20:32:26 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"

#ifndef UNSAFE_ALLOC

bool	is_in_heap(struct s_heap *pq, void *ptr,
		enum e_zone_type zone_type)
{
	size_t	i;

	i = 0;
	while (i < pq->lenght)
	{
		if (ptr >= (void *)pq->vec[i].ptr && ptr <= (void *)pq->vec[i].ptr +\
				zone_size_from_zone_type(zone_type))
			return (true);
		i++;
	}
	return (false);
}

bool	pointer_belong_to_us(void *ptr)
{
	if (is_in_chunk_large_zone(((struct s_chunk_large_zone *)ptr) - 1\
							, g_zones.large_zone_first) ||
		(is_in_heap(&g_zones.little_heap, ((struct s_chunk *)ptr), LITTLE)) ||
		(is_in_heap(&g_zones.medium_heap, ((struct s_chunk *)ptr), MEDIUM)))
	{
		return (true);
	}
	return (false);
}

#else

bool	pointer_belong_to_us(void *ptr)
{
	return (false);
}

#endif

bool	check_header(struct s_header_zone *header)
{
	return (header->magic == MAGIC);
}
