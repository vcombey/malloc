/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sift.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:54:29 by vcombey           #+#    #+#             */
/*   Updated: 2018/05/20 14:06:49 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"

void				swap_nodes(struct s_zone_ref *a,\
		struct s_zone_ref *b)
{
	struct s_zone_ref tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
	a->ptr->parent = a;
	b->ptr->parent = b;
}

struct s_zone_ref	*max_free_space(struct s_zone_ref *a,\
		struct s_zone_ref *b)
{
	if (!a)
		return (b);
	if (!b)
		return (a);
	return (a->free_space > b->free_space ? a : b);
}

struct s_zone_ref	*max_free_space_children(struct s_heap *pq,\
		size_t pos)
{
	struct s_zone_ref *node;
	struct s_zone_ref *left;
	struct s_zone_ref *right;

	node = &pq->vec[pos];
	left = (pos * 2 + 1 < pq->lenght) ? &pq->vec[pos * 2 + 1] : NULL;
	right = (pos * 2 + 2 < pq->lenght) ? &pq->vec[pos * 2 + 2] : NULL;
	return (max_free_space(max_free_space(right, left), node));
}

void				sift_down(struct s_heap *pq, size_t pos)
{
	struct s_zone_ref *max;
	struct s_zone_ref *node;

	while (true)
	{
		node = &pq->vec[pos];
		max = max_free_space_children(pq, pos);
		if (node == max)
			return ;
		else
			swap_nodes(node, max);
		pos = max - pq->vec;
	}
}

void				sift_up(struct s_heap *pq, size_t pos)
{
	while (pos > 0 && pq->vec[pos].free_space > pq->vec[pos / 2].free_space)
	{
		swap_nodes(&pq->vec[pos], &pq->vec[pos / 2]);
		pos /= 2;
	}
}
