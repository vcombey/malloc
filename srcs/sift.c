#include "malloc.h"
#include "internal_malloc.h"

void					swap_nodes(struct zone_reference *a,\
		struct zone_reference *b)
{
	struct zone_reference tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
	a->ptr->parent = a;
	b->ptr->parent = b;
}

struct zone_reference	*max_free_space(struct zone_reference *a,\
		struct zone_reference *b)
{
	if (!a)
		return (b);
	if (!b)
		return (a);
	return (a->free_space > b->free_space ? a : b);
}

struct zone_reference	*max_free_space_children(struct priority_queue *pq,\
		size_t pos)
{
	struct zone_reference *node;
	struct zone_reference *left;
	struct zone_reference *right;

	node = &pq->vec[pos];
	left = (pos * 2 + 1 < pq->lenght) ? &pq->vec[pos * 2 + 1] : NULL;
	right = (pos * 2 + 2 < pq->lenght) ? &pq->vec[pos * 2 + 2] : NULL;
	return (max_free_space(max_free_space(right, left), node));
}

void					sift_down(struct priority_queue *pq, size_t pos)
{
	struct zone_reference *max;
	struct zone_reference *node;

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

void					sift_up(struct priority_queue *pq, size_t pos)
{
	while (pos > 0 && pq->vec[pos].free_space > pq->vec[pos / 2].free_space)
	{
		swap_nodes(&pq->vec[pos], &pq->vec[pos / 2]);
		pos /= 2;
	}
}
