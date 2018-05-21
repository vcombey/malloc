/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:54:29 by vcombey           #+#    #+#             */
/*   Updated: 2018/05/20 18:29:51 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"
#include <string.h>
#include <assert.h>
#include <pthread.h>

//static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

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
	//ft_putstr("boujour\n");
	z->init = true;
	z->page_size = getpagesize();
}

void	*malloc(size_t size)
{
//	ft_putstr("malloc\n");
	//pthread_mutex_lock(&g_mutex);
	if (!g_zones.init)
		constructor(&g_zones);
	void *addr = allocator(&g_zones, size);
	assert((size_t)addr % 8 == 0);
	//ft_putstr("out malloc\n");
	//pthread_mutex_unlock(&g_mutex);
	return (addr);
}

void	*calloc(size_t count, size_t size)
{
	//ft_putstr("calloc\n");
	void *addr;

	addr = malloc(count * size);
	if (addr)
		bzero(addr, count * size);
	return (addr);
}

void	free(void *ptr)
{
	//pthread_mutex_lock(&g_mutex);
	if (!g_zones.init)
		constructor(&g_zones);
	desalocator(ptr);
	//pthread_mutex_unlock(&g_mutex);
}

void	*realloc(void *ptr, size_t size)
{
	//ft_putstr("realloc\n");
	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return NULL;
	}
	//pthread_mutex_lock(&g_mutex);
	if (!g_zones.init)
		constructor(&g_zones);
	if ((size_t)ptr % 8 != 0)
	{
		printf("bad allignement\n");
		//pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	void *addr = reallocator(ptr, size);
//	printf("addr: %zu\n", (size_t)addr);
	//pthread_mutex_unlock(&g_mutex);
	return (addr);
}

void	*reallocf(void *ptr, size_t size)
{
	//ft_putstr("reallocf\n");
	return realloc(ptr, size);
}
