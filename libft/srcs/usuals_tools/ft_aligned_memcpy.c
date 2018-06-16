#include "libft.h"

/*
** XXX This function is not secure ! Only size multiplied by 8 works !
*/

void	*ft_aligned_memcpy(
	void *restrict dst,
	const void *restrict src,
	size_t n)
{
	uint64_t *src1;
	uint64_t *dst1;

	if (src == dst)
		return ((void *)src);
	src1 = (uint64_t *)src;
	dst1 = (uint64_t *)dst;
	n >>= 3;
	while (n--)
		*dst1++ = *src1++;
	return (dst);
}
