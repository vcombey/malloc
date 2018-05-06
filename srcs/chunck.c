#include "malloc.h"
#include "internal_malloc.h"

void	add_chunk_large_zone(struct chunk_large_zone **first,\
		struct chunk_large_zone *new)
{
	new->next = *first;
	new->prev = NULL;
	if (*first)
	{
		(*first)->prev = new;
	}
	*first = new;
}

void	del_chunk_large_zone(struct chunk_large_zone **first,\
		struct chunk_large_zone *node)
{
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (node == *first)
		*first = node->next;
}

size_t	len_chunk_large_zone(struct chunk_large_zone *first)
{
	size_t	i;

	i = 0;
	while (first)
	{
		first = first->next;
		i++;
	}
	return (i);
}

bool	is_in_chunk_large_zone(struct chunk_large_zone *node, struct chunk_large_zone *first)
{
	while (first)
	{
		if (first == node)
			return true;
		first = first->next;
	}
	return (false);

}
