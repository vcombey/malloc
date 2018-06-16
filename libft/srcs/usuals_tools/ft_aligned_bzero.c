#include "libft.h"

/*
** XXX This function is not secure ! Only size multiplied by 8 works !
*/

void	ft_aligned_bzero(void *s, size_t n)
{
	uint64_t *dst;

	dst = (uint64_t *)s;
	n >>= 3;
	while (n--)
		*dst++ = (uint64_t)0;
}
