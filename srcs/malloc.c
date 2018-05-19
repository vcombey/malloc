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
struct s_zones g_zones;

void	constructor(struct s_zones *z)
{
	ft_putstr("boujour\n");
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
	assert((size_t)addr % 8 == 0);
	return (addr);
}

void	*calloc(size_t count, size_t size)
{
	ft_putstr("calloc\n");
	void *addr;

	addr = malloc(count * size);
	if (addr)
		bzero(addr, count * size);
	return (addr);
}

void	*valloc(size_t size)
{
	ft_putstr("valloc\n");
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
}

void	*realloc(void *ptr, size_t size)
{
	ft_putstr("realloc\n");
	if (!g_zones.init)
		constructor(&g_zones);
	if (ptr == NULL)
		return (malloc(size));
	//if (size == 0)
	//	return (free(size));
	//TODO: size = 0 -> free
	if ((size_t)ptr % 8 != 0)
	{
		printf("bad allignement\n");
		return (NULL);
	}
	void *addr = reallocator(ptr, size);
	return (addr);
}

void	*reallocf(void *ptr, size_t size)
{
	ft_putstr("reallocf\n");
	return realloc(ptr, size);
}
