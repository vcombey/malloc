/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aligned_memcpy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:00:15 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/17 17:00:28 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** XXX This function is not secure ! Only size multiplied by 8 works !
*/

void	*ft_aligned_memcpy(
	void *restrict dst,
	const void *restrict src,
	size_t n)
{
	uint64_t *src1;
	uint64_t *dst1;

	if (src == dst)
		return ((void *)src);
	src1 = (uint64_t *)src;
	dst1 = (uint64_t *)dst;
	n >>= 3;
	while (n--)
		*dst1++ = *src1++;
	return (dst);
}
