/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:00:15 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/17 17:00:28 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_printf.h"

void	cast_u(uintmax_t *n, t_length mask)
{
	if (mask == VOID)
		*n = (t_u_int)(*n);
	else if (mask == H)
		*n = (t_su_int)(*n);
	else if (mask == HH)
		*n = (t_u_char)(*n);
	else if (mask == L)
		*n = (t_lu_int)(*n);
	else if (mask == LL)
		*n = (t_llu_int)(*n);
	else if (mask == Z)
		*n = (size_t)(*n);
}

void	cast_i(intmax_t *n, t_length mask)
{
	if (mask == VOID)
		*n = (int)(*n);
	else if (mask == H)
		*n = (t_s_int)(*n);
	else if (mask == HH)
		*n = (char)(*n);
	else if (mask == L)
		*n = (t_l_int)(*n);
	else if (mask == LL)
		*n = (t_ll_int)(*n);
	else if (mask == Z)
		*n = (size_t)(*n);
}
