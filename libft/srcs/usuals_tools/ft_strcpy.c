#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char *origin;

	origin = dst;
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
	return (origin);
}
