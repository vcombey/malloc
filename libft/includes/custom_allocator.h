#ifndef CUSTOM_ALLOCATOR_H
# define CUSTOM_ALLOCATOR_H

# include <stdlib.h>

struct				s_custom_memory_fn
{
	void			*(*allocator)(size_t);
	void			(*deallocator)(void *);
};

#endif
