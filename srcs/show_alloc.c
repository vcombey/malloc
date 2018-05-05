#include "malloc.h"
#include "internal_malloc.h"

void					show_alloc_chunk(void *ptr,\
		enum e_zone_type zone_type,\
		size_t *i)
{
	struct chunk *c = (struct chunk *)((size_t)ptr + get_offset_zone_header(zone_type) + *i * get_zone_block(zone_type));
	size_t inf = (size_t)c + sizeof(*c);
	size_t sup = (size_t)c + c->size_block * get_zone_block(zone_type);
	printf("%#zx - %#zx: %zu octets\n", inf, sup, sup - inf);
	*i += c->size_block;
}

void					show_alloc_zone(struct zone_reference zone_ref,\
		enum e_zone_type zone_type)
{
	size_t		i;
	__uint128_t	bitmask;

	i = 0;
	while (i < 128)
	{
		bitmask = 1;
		bitmask <<= i;
		if (zone_ref.allocated_chunks & bitmask)
			show_alloc_chunk(zone_ref.ptr, zone_type, &i);
		else
			i++;
	}
}

struct zone_reference	find_minimum_addr(struct priority_queue pq,\
		struct zone_reference previous_min)
{
	size_t					i;
	struct zone_reference	new_min;

	i = 0;
	new_min = (struct zone_reference){.ptr=NULL};
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

void					show_alloc_priority_queue(struct priority_queue pq,\
		enum e_zone_type zone_type)
{
	size_t					i;
	struct zone_reference	min;

	i = 0;
	min = (struct zone_reference){.ptr=NULL};
	while (i < pq.lenght)
	{
		min = find_minimum_addr(pq, min);
		show_alloc_zone(min, zone_type);
		printf("\n");
		i++;
	}
}

void	show_alloc_mem(void)
{
	printf("TINY: \n");
	show_alloc_priority_queue(g_zones.little_heap, LITTLE);
	printf("SMALL: \n");
	show_alloc_priority_queue(g_zones.medium_heap, MEDIUM);
	printf("LARGE: \n");
	show_alloc_large_zone(g_zones.large_zone_first);
}
