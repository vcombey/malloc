#include "malloc.h"
#include "internal_malloc.h"

void	ft_memcpy_align(void *dest, void *src, size_t size)
{
	unsigned long	*dest_cast = dest;
	unsigned long	*src_cast = src;
	size_t			i = 0;

	while (i < size)
	{
		dest_cast[i] = src_cast[i];
		i += 8;
	}
}

void    print_binary(__uint128_t nb) {
	for (int i = 0; i < 128; i++)
	{
		printf("%i", (int)(nb % 2));
		nb >>= 1;
	}
	printf("\n");
}

void	unimplemented(char *mess)
{
	printf("%s", mess);
	exit(1);
}

void	panic(char *mess)
{
	printf("%s", mess);
	exit(1);
}

