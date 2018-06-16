#include "libft.h"

void	ft_putnbr(int n)
{
	int		exponent;
	int		sign;
	int		i;
	char	buff;

	sign = (n < 0) ? 1 : 0;
	exponent = 1;
	i = n;
	while ((i = i / 10))
		exponent *= 10;
	if (sign)
		write(1, "-", 1);
	while (exponent)
	{
		i = n / exponent;
		buff = (sign) ? HEX_T(-(i % 10)) : HEX_T((i % 10));
		n -= i * exponent;
		write(1, &buff, 1);
		exponent /= 10;
	}
}
