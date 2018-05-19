#include "malloc.h"
#include "internal_malloc.h"
#include <string.h>

void	recalc_header_zone(struct zone_reference *new_vec, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		new_vec[i].ptr->parent = &new_vec[i];
		i++;
	}
}

int		add_priority_queue(struct priority_queue *pq,\
		struct zone_reference new_node)
{
	void *new_vec;

	if (pq->lenght == pq->size)
	{
		if ((new_vec = mmap(NULL,\
						pq->size * sizeof(*pq->vec) + g_zones.page_size,\
						PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0))\
				== MAP_FAILED)
			return (-1);
		memmove(new_vec, pq->vec, pq->lenght * sizeof(*pq->vec));
		recalc_header_zone(new_vec, pq->lenght);
		munmap(pq->vec, pq->size * sizeof(*pq->vec));
		pq->size += g_zones.page_size / sizeof(*pq->vec);
		pq->vec = new_vec;
	}
	new_node.ptr->parent = &pq->vec[pq->lenght];
	pq->vec[pq->lenght] = new_node;
	sift_up(pq, pq->lenght);
	pq->lenght += 1;
	return (0);
}

void	del_priority_queue(struct priority_queue *pq, size_t pos,\
		enum e_zone_type zone_type)
{
	munmap(pq->vec[pos].ptr, zone_size_from_zone_type(zone_type));
	if (pos != pq->lenght - 1) {
		pq->vec[pos] = pq->vec[pq->lenght - 1];
		pq->vec[pos].ptr->parent = &pq->vec[pos];
		bzero(&pq->vec[pq->lenght - 1], sizeof(pq->vec[pq->lenght - 1]));
		pq->lenght--;
		sift_down(pq, pos);
	}
	else
		pq->lenght--;
}

void	update_priority_queue(struct priority_queue *pq,\
		struct zone_reference *zone_ref,\
		enum e_zone_type zone_type)
{
	size_t	pos;

	pos = zone_ref - pq->vec;
	if (zone_ref->free_space == 128 && pq->vec[0].free_space == 128 && pos != 0)
	{
		printf("del priority_queue\n");
		del_priority_queue(pq, pos, zone_type);
	}
	else
	{
		printf("sift up\n");
		sift_up(pq, pos);
	}
}

bool	is_in_priority_queue(struct priority_queue *pq, void *ptr,
		enum e_zone_type zone_type)
{
	size_t	i = 0;

	while (i < pq->lenght)
	{
		if (ptr >= (void *)pq->vec[i].ptr && ptr <= (void *)pq->vec[i].ptr + zone_size_from_zone_type(zone_type))
			return true;
		i++;
	}
	return false;
}

struct priority_queue	*get_priority_queue(struct zones *zones, enum e_zone_type zone_type)
{
	if (zone_type == LITTLE)
		return &zones->little_heap;
	else if (zone_type == MEDIUM)
		return &zones->medium_heap;
	return NULL;
}
