#include "malloc.h"
#include "internal_malloc.h"
#include <string.h>

struct zones g_zones;

void	constructor(struct zones *z)
{
	z->init = true;
	z->page_size = getpagesize();
}

void	*malloc(size_t size)
{
	dprintf(2, "malloc\n");
	if (size <= 0)
		return (NULL);
	if (!g_zones.init)
		constructor(&g_zones);
	return (allocator(&g_zones, size));
}

void	free(void *ptr)
{
	dprintf(2, "free\n");
	if (ptr == NULL || (size_t)ptr % 8 != 0)
		return ;
	if (!g_zones.init)
		constructor(&g_zones);
	desalocator(ptr);
}

void	*realloc(void *ptr, size_t size)
{
	dprintf(2, "realloc\n");
	if (ptr == NULL || (size_t)ptr % 8 != 0)
		return (NULL);
	if (!g_zones.init)
		constructor(&g_zones);
	return (reallocator(ptr, size));
}
