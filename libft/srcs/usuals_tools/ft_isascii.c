#include "libft.h"

int		ft_isascii(int c)
{
	if (c >> 7)
		return (0);
	return (1);
}
