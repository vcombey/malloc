#ifndef MALLOC_H
# define MALLOC_H

#include <stdlib.h>

#define malloc ft_malloc
#define free ft_free
#define realloc ft_realloc

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem(void);

void	*calloc(size_t count, size_t size);
void	*valloc(size_t size);
void	*reallocf(void *ptr, size_t size);
#endif
