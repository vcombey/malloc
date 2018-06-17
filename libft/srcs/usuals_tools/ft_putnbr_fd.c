/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:00:15 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/17 17:00:28 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
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
		write(fd, "-", 1);
	while (exponent)
	{
		i = n / exponent;
		buff = (sign) ? HEX_T(-(i % 10)) : HEX_T((i % 10));
		n -= i * exponent;
		write(fd, &buff, 1);
		exponent /= 10;
	}
}
