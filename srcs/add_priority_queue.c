/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_priority_queue.c                               :+:      :+:    :+:   */
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
