/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parrpush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:39 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:04 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_parrpush(void ***tab, void *elem)
{
	void			**n_tab;
	unsigned int	arr_len;

	arr_len = ft_parrlen(*tab);
	n_tab = (arr_len % 8) ? *tab :
	(void **)ft_memalloc(sizeof(void*) * (arr_len + 8 + 1));
	n_tab[arr_len] = elem;
	n_tab[arr_len + 1] = (void*)0;
	if (n_tab == *tab)
		return ;
	while (arr_len--)
		n_tab[arr_len] = (*tab)[arr_len];
	free(*tab);
	*tab = n_tab;
}
