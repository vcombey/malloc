#include "str.h"
#include "alloc.h"
#include "mem.h"

char	*ft_itoa(int n)
{
	return (ft_itoa_base(n, 10));
}

int		itoa_base_len(intmax_t value, int base)
{
	int		nb_digit;

	if (value == 0)
		return (1);
	value *= (value > 0) ? -1 : 1;
	nb_digit = 0;
	while (value < 0)
	{
		value /= base;
		nb_digit++;
	}
	return (nb_digit);
}

char	*ft_itoa_base_str(intmax_t value, char *str, int base)
{
	int		nb_digit;
	int		neg;

	if (value == 0)
		return (ft_strdup("0"));
	nb_digit = itoa_base_len(value, base);
	neg = (base == 10 && value < 0) ? 1 : 0;
	value *= (value > 0) ? -1 : 1;
    if (!str)
        str = (char *)palloc((sizeof(char) * nb_digit) + neg + 1);
	ft_bzero(str, nb_digit + neg + 1);
	str[0] = '-';
	nb_digit -= 1 - neg;
	while (nb_digit-- >= neg)
	{
		str[nb_digit + 1] = -(value % base) \
							+ ((-(value % base) > 9) ? 'a' - 10 : '0');
		value /= base;
	}
	return (str);
}

char	*ft_sizetoa_base_str(size_t value, char *str, int base)
{
	int		nb_digit;

    if (value == 0)
    {
        if (!str) 
            return (ft_strdup("0"));
        else
            str[0] = '0';
        return str;
    }
    nb_digit = itoa_base_len(value, base);
    if (!str)
        str = (char *)palloc((sizeof(char) * nb_digit) + 1);
    ft_bzero(str, nb_digit + 1);
    str[0] = '-';
    nb_digit -= 1;
    while (nb_digit-- >= 0)
    {
        str[nb_digit + 1] = (value % base) \
                            + (((value % base) > 9) ? 'a' - 10 : '0');
        value /= base;
    }
    return (str);
}

char	*ft_itoa_base(intmax_t value, int base)
{
    return (ft_itoa_base_str(value, NULL, base));
}

int		uitoa_base_len(uintmax_t value, int base)
{
    int		nb_digit;

    nb_digit = 0;
    while (value > 0)
    {
        value /= base;
        nb_digit++;
    }
    return (nb_digit);
}

char	*ft_unsigned_itoa_base(uintmax_t value, int base)
{
    int		nb_digit;
    char	*str;

    if (value == 0)
        return (ft_strdup("0"));
    nb_digit = uitoa_base_len(value, base);
    if (!(str = ft_strnew(nb_digit)))
        return (NULL);
    nb_digit--;
    while (nb_digit >= 0)
    {
        str[nb_digit] = (value % base) + ((value % base > 9) ? 'a' - 10 : '0');
        value /= base;
        nb_digit--;
    }
    return (str);
}
