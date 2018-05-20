/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_queue.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:54:29 by vcombey           #+#    #+#             */
/*   Updated: 2018/05/20 14:34:26 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"
#include <string.h>

static void	recalc_header_zone(struct s_zone_ref *new_vec, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		new_vec[i].ptr->parent = &new_vec[i];
		i++;
	}
}

static	int	realloc_heap(struct s_heap *pq)
{
	void	*new_vec;
	size_t	new_size;

	new_size = pq->size == 0 ? 4096 : 2 * pq->size;
	if ((new_vec = mmap(NULL,\
					new_size * sizeof(*pq->vec),\
					PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))\
			== MAP_FAILED)
		return (-1);
	memmove(new_vec, pq->vec, pq->lenght * sizeof(*pq->vec));
	recalc_header_zone(new_vec, pq->lenght);
	munmap(pq->vec, pq->size * sizeof(*pq->vec));
	pq->size = new_size;
	pq->vec = new_vec;
	return (0);
}

int			add_heap(struct s_heap *pq,\
		struct s_zone_ref new_node)
{
	if (pq->lenght == pq->size)
	{
		if (realloc_heap(pq) == -1)
			return (-1);
	}
	new_node.ptr->parent = &pq->vec[pq->lenght];
	pq->vec[pq->lenght] = new_node;
	sift_up(pq, pq->lenght);
	pq->lenght += 1;
	return (0);
}

void		del_heap(struct s_heap *pq, size_t pos,\
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

void		update_heap(struct s_heap *pq,\
		struct s_zone_ref *zone_ref,\
		enum e_zone_type zone_type)
{
	size_t	pos;

	pos = zone_ref - pq->vec;
	if (zone_ref->free_space == 128 && pq->vec[0].free_space == 128 && pos != 0)
	{
		del_heap(pq, pos, zone_type);
	}
	else
	{
		sift_up(pq, pos);
	}
}

bool		is_in_heap(struct s_heap *pq, void *ptr,
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

struct s_heap	*get_heap(struct s_zones *zones, enum e_zone_type zone_type)
{
	if (zone_type == LITTLE)
		return (&zones->little_heap);
	else if (zone_type == MEDIUM)
		return (&zones->medium_heap);
	return (NULL);
}
