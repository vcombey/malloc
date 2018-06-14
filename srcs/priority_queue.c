/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:54:29 by vcombey           #+#    #+#             */
/*   Updated: 2018/05/20 20:34:57 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"
#include <string.h>

void			del_heap(struct s_heap *pq, size_t pos,\
		enum e_zone_type zone_type)
{
	munmap(pq->vec[pos].ptr, zone_size_from_zone_type(zone_type));
	if (pos != pq->lenght - 1)
	{
		pq->vec[pos] = pq->vec[pq->lenght - 1];
		pq->vec[pos].ptr->parent = &pq->vec[pos];
		bzero(&pq->vec[pq->lenght - 1], sizeof(pq->vec[pq->lenght - 1]));
		pq->lenght--;
		sift_down(pq, pos);
	}
	else
		pq->lenght--;
}

void			update_heap(struct s_heap *pq,\
		struct s_zone_ref *zone_ref,\
		enum e_zone_type zone_type)
{
	size_t	pos;

	pos = zone_ref - pq->vec;
	if (zone_ref->free_space == NB_BLOCK_ZONE && \
		pq->vec[0].free_space == NB_BLOCK_ZONE && pos != 0)
	{
		del_heap(pq, pos, zone_type);
	}
	else
	{
		sift_up(pq, pos);
	}
}

struct s_heap	*get_heap(struct s_zones *zones, enum e_zone_type zone_type)
{
	if (zone_type == LITTLE)
		return (&zones->little_heap);
	else if (zone_type == MEDIUM)
		return (&zones->medium_heap);
	return (NULL);
}
