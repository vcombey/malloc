/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:00:17 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/17 17:00:28 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	size_t src_len;
	size_t dst_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	dst_len = 0;
	while (*dst++)
		dst_len++;
	dst -= 1;
	if (dst_len >= size)
		return (size + src_len);
	size -= dst_len + 1;
	while (*src && size--)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len + dst_len);
}
