#include "malloc.h"
#include "internal_malloc.h"
#include <string.h>

struct zones g_zones;

void	constructor(struct zones *z)
{
	z->init = true;
	z->page_size = getpagesize();
}

void	*ft_malloc(size_t size)
{
	if (size <= 0)
		return (NULL);
	if (!g_zones.init)
		constructor(&g_zones);
	return (allocator(&g_zones, size));
}

void	ft_free(void *ptr)
{
	if (ptr == NULL || (size_t)ptr % 8 != 0)
		return ;
	if (!g_zones.init)
		constructor(&g_zones);
	desalocator(ptr);
}

void	*ft_realloc(void *ptr, size_t size)
{
	if (ptr == NULL || (size_t)ptr % 8 != 0)
		return (NULL);
	if (!g_zones.init)
		constructor(&g_zones);
	return (reallocator(ptr, size));
}
