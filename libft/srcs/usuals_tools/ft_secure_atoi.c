/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secure_atoi.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:00:15 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/17 17:00:28 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		secure_mul(int a, int b, bool *error)
{
	if (a > INT_MAX / b)
		*error = true;
	if ((a < INT_MIN / b))
		*error = true;
	if ((a == -1) && (b == INT_MIN))
		*error = true;
	if ((b == -1) && (a == INT_MIN))
		*error = true;
	return (a * b);
}

static int		secure_add(int a, int b, bool *error)
{
	if ((a > 0) && (b > INT_MAX - a))
		*error = true;
	if ((a < 0) && (b < INT_MIN - a))
		*error = true;
	return (a + b);
}

int				ft_secure_atoi(const char *nptr, bool *error)
{
	int result;
	int sign;

	*error = false;
	result = 0;
	sign = false;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = true;
		nptr++;
	}
	if (!(*nptr >= '0' && *nptr <= '9'))
		*error = true;
	else
		while (*nptr >= '0' && *nptr <= '9')
		{
			result = secure_mul(result, 10, error);
			result = secure_add(result, ((sign) ?
				-1 * (*nptr - '0') : (*nptr - '0')), error);
			nptr++;
		}
	if (*nptr != '\0')
		*error = true;
	return (result);
}
