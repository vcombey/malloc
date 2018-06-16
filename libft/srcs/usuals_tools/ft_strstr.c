#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t len;

	if (!(len = ft_strlen(little)))
		return ((char *)big);
	while (*big)
	{
		if (*big == *little)
		{
			if (ft_strncmp(big, little, len) == 0)
				return ((char *)big);
		}
		big++;
	}
	return (NULL);
}
