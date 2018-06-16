#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	while (*s1)
		if (*s1++ != *s2++)
			return (0);
	if (!*s2)
		return (1);
	return (0);
}
