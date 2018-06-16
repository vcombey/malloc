#include "libft.h"

size_t	ft_strlen(const char *s)
{
	const char *t;

	t = s;
	while (*t)
		t++;
	return (t - s);
}
