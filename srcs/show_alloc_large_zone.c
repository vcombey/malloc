#include "malloc.h"
#include "internal_malloc.h"

struct chunk_large_zone	*find_min_large_zone(struct chunk_large_zone *first,\
		void *previous_min)
{
	void					*new_min;
	struct chunk_large_zone	*tmp;

	new_min = NULL;
	tmp = first;
	while (tmp)
	{
		if ((new_min == NULL ||\
		(size_t)tmp < (size_t)new_min) && (size_t)tmp > (size_t)previous_min)
		{
			new_min = tmp;
		}
		tmp = tmp->next;
	}
	return (new_min);
}

void					show_alloc_large_zone(\
		struct chunk_large_zone *large_zone_first)
{
	size_t					len;
	size_t					i;
	struct chunk_large_zone	*min;

	len = len_chunk_large_zone(large_zone_first);
	i = 0;
	min = NULL;
	while (i < len)
	{
		min = find_min_large_zone(large_zone_first, min);
		printf("%#zx - %#zx: %zu octets\n", (size_t)min + sizeof(*min), (size_t)min + (min->data.size_block / g_zones.page_size + 1) * g_zones.page_size, min->size_octet);
		i++;
	}
}
