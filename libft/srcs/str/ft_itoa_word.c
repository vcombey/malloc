/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:40 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:06 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include "alloc.h"
#include "mem.h"

char	*ft_itoa_base_word(int n, char nbr[20], int base)
{
	ft_bzero(nbr, 20);
    return (ft_itoa_base_str(n, (char*)nbr, base));
}

char	*ft_sizetoa_base_word(size_t n, char nbr[20], int base)
{
	ft_bzero(nbr, 20);
    return (ft_sizetoa_base_str(n, (char*)nbr, base));
}
