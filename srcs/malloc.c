/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:54:29 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/03 20:40:15 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"
#include <string.h>
#include <assert.h>
#include <pthread.h>

static pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

struct s_zones g_zones;

void	constructor(struct s_zones *z)
{
	z->init = true;
	z->page_size = getpagesize();
}

void	*malloc(size_t size)
{
	void *addr;

	pthread_mutex_lock(&g_mutex);
	if (!g_zones.init)
		constructor(&g_zones);
	addr = allocator(&g_zones, size);
	assert((size_t)addr % 16 == 0);
	pthread_mutex_unlock(&g_mutex);
	return (addr);
}

void	*calloc(size_t count, size_t size)
{
	void	*addr;
	size_t	global_size;

	global_size = count * size;
	if (global_size == 0)
		global_size = 32;
	addr = malloc(global_size);
	if (addr)
		bzero(addr, global_size);
	return (addr);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	if (!g_zones.init)
		constructor(&g_zones);
	desalocator(ptr);
	pthread_mutex_unlock(&g_mutex);
}

void	*realloc(void *ptr, size_t size)
{
	void *addr;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	pthread_mutex_lock(&g_mutex);
	if (!g_zones.init)
		constructor(&g_zones);
	if ((size_t)ptr % 16 != 0)
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	addr = reallocator(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (addr);
}

void	*reallocf(void *ptr, size_t size)
{
	return (realloc(ptr, size));
}
