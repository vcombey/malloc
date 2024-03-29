/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:54:29 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/03 20:37:23 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"

void					show_alloc_chunk(void *ptr,\
		enum e_zone_type zone_type,\
		size_t *i)
{
	struct s_chunk	*c;
	size_t			inf;
	size_t			sup;

	c = (struct s_chunk *)((size_t)ptr + offset_zone_header(zone_type) + \
			*i * zone_block_from_zone_type(zone_type));
	inf = (size_t)c + sizeof(*c);
	sup = (size_t)c + c->size_block * zone_block_from_zone_type(zone_type);
	ft_printf("%#zx - %#zx: %zu octets\n", inf, sup, sup - inf);
	*i += c->size_block;
}

void					show_alloc_zone(struct s_zone_ref zone_ref,\
		enum e_zone_type zone_type)
{
	size_t		i;
	__uint128_t	bitmask;

	i = 0;
	while (i < NB_BLOCK_ZONE)
	{
		bitmask = 1;
		bitmask <<= i;
		if (zone_ref.allocated_chunks & bitmask)
			show_alloc_chunk(zone_ref.ptr, zone_type, &i);
		else
			i++;
	}
}

struct s_zone_ref		find_minimum_addr(struct s_heap pq,\
		struct s_zone_ref previous_min)
{
	size_t					i;
	struct s_zone_ref		new_min;

	i = 0;
	new_min = (struct s_zone_ref){.ptr=NULL};
	while (i < pq.lenght)
	{
		if ((new_min.ptr == NULL || pq.vec[i].ptr < new_min.ptr)\
				&& pq.vec[i].ptr > previous_min.ptr)
		{
			new_min = pq.vec[i];
		}
		i++;
	}
	return (new_min);
}

void					show_alloc_heap(struct s_heap pq,\
		enum e_zone_type zone_type)
{
	size_t					i;
	struct s_zone_ref		min;

	i = 0;
	min = (struct s_zone_ref){.ptr=NULL};
	while (i < pq.lenght)
	{
		ft_printf("i %zu, length %zu\n", i, pq.lenght);
		min = find_minimum_addr(pq, min);
		show_alloc_zone(min, zone_type);
		ft_printf("\n");
		i++;
	}
}

void					show_alloc_mem(void)
{
	ft_printf("TINY: \n");
	show_alloc_heap(g_zones.little_heap, LITTLE);
	ft_printf("SMALL: \n");
	show_alloc_heap(g_zones.medium_heap, MEDIUM);
	ft_printf("LARGE: \n");
	show_alloc_large_zone(g_zones.large_zone_first);
}
