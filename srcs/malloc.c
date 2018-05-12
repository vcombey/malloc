#include "malloc.h"
#include "internal_malloc.h"
#include <string.h>
#include <assert.h>

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
	assert((size_t)addr % 8 == 0);
	return (addr);
}

void	*calloc(size_t count, size_t size)
{
	void *addr;

	ft_putstr("calloc\n");
	addr = malloc(count * size);
	if (addr)
		bzero(addr, count * size);
	return (addr);
}

void	*valloc(size_t size)
{
	return malloc(size);
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
	if (!g_zones.init)
		constructor(&g_zones);
	ft_putstr("realloc\n");
	if (ptr == NULL) {
		return malloc(size);
	}
	if ((size_t)ptr % 8 != 0)
	{
		printf("bad allignement\n");
		return (NULL);
	}
	void *addr = reallocator(ptr, size);
	ft_putstr("tout va bien\n");
	return (addr);
}

void	*reallocf(void *ptr, size_t size)
{
	return realloc(ptr, size);
}
