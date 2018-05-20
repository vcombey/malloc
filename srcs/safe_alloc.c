/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:57:10 by vcombey           #+#    #+#             */
/*   Updated: 2018/05/20 14:25:32 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"

bool	pointer_belong_to_us(void *ptr)
{
	if (is_in_chunk_large_zone(((struct s_chunk_large_zone *)ptr) - 1, g_zones.large_zone_first) ||
			(is_in_heap(&g_zones.little_heap, ((struct s_chunk *)ptr), LITTLE)) ||
			(is_in_heap(&g_zones.medium_heap, ((struct s_chunk *)ptr), MEDIUM)))
	{
	//	printf("pointer belong to us\n");
		return (true);
	}
	return (false);
}

bool	check_header(struct s_header_zone *header)
{
	return (header->magic == MAGIC);
}

