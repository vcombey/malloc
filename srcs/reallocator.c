/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:54:29 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/03 20:32:48 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"
#include <string.h>

void	*reallocator(void *ptr, size_t size)
{
	struct s_chunk	*chunk;

	chunk = ((struct s_chunk *)ptr) - 1;
	if (!pointer_belong_to_us(ptr))
	{
		ft_printf("pointer being reallocated was not allocated\n");
		return (NULL);
	}
	if (chunk->is_free)
	{
		ft_printf("double free\n");
		return (NULL);
	}
	if (chunk->zone_type == LARGE)
		return (realloc_large_zone(ptr, size));
	else if (chunk->zone_type == LITTLE)
		return (realloc_zone(ptr, chunk, size));
	else if (chunk->zone_type == MEDIUM)
		return (realloc_zone(ptr, chunk, size));
	return (NULL);
}
