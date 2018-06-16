#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;

	i = ft_strlen(little);
	if (i == 0)
		return ((char *)big);
	while (*big && len >= i)
	{
		if (ft_strncmp(big, little, i) == 0)
			return ((char *)big);
		len--;
		big++;
	}
	return (NULL);
}
