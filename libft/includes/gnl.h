#ifndef GNL_H
# define GNL_H

# include "custom_allocator.h"

/*
** Return the next newline of a file descriptor.
*/

int					get_next_line(
		const int fd,
		char **line,
		struct s_custom_memory_fn *mem);

#endif
