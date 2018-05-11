#include "malloc.h"
#include "internal_malloc.h"
#include <string.h>

void	ft_putstr(char *str)
{
	while (*str)
	{ 
		write(1, str, 1);
		str++;
	}
}
struct zones g_zones;

void	constructor(struct zones *z)
{
	z->init = true;
	z->page_size = getpagesize();
}

void	*malloc(size_t size)
{
	ft_putstr("malloc\n");
	if (size <= 0)
		return (NULL);
	if (!g_zones.init)
		constructor(&g_zones);
	void *addr = allocator(&g_zones, size);
	ft_putstr("tout va bien\n");
	return (addr);
}

void	free(void *ptr)
{
	ft_putstr("free\n");
	if (ptr == NULL || (size_t)ptr % 8 != 0)
	{
		ft_putstr("bad alignement free\n");
		return ;
	}
	if (!g_zones.init)
		constructor(&g_zones);
	desalocator(ptr);
	ft_putstr("tout va bien\n");
}

void	*realloc(void *ptr, size_t size)
{
	ft_putstr("realloc\n");
	if (ptr == NULL || (size_t)ptr % 8 != 0)
	{
		printf("bad allignement\n");
		return (NULL);
	}
	if (!g_zones.init)
		constructor(&g_zones);
	void *addr = reallocator(ptr, size);
	ft_putstr("tout va bien\n");
	return (addr);
}
