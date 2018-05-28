/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 13:54:29 by vcombey           #+#    #+#             */
/*   Updated: 2018/05/26 23:11:18 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "internal_malloc.h"

void	ft_memcpy_align(void *dest, void *src, size_t size)
{
	unsigned long long	*dest_cast;
	unsigned long long	*src_cast;
	size_t			i;

	dest_cast = dest;
	src_cast = src;
	i = 0;
	while (i < size / 8)
	{
		dest_cast[i] = src_cast[i];
		i += 1;
	}
}

void	print_binary(__uint128_t nb)
{
	for (int i = 0; i < NB_BLOCK_ZONE; i++)
	{
		//printf("%i", (int)(nb % 2));
		nb >>= 1;
	}
	//printf("\n");
}

void	unimplemented(char *mess)
{
    (void)mess;
	//printf("%s", mess);
	exit(1);
}

void	panic(char *mess)
{
    (void)mess;
	//printf("%s", mess);
	exit(1);
}
