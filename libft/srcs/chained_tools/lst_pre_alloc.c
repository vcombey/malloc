/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pre_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:00:15 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/17 17:00:28 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chained_tools.h"

struct s_list	*lst_pre_alloc(
		struct s_list **alst,
		size_t len,
		void *(*allocator)(size_t),
		void (*deallocator)(void *))
{
	struct s_list *m;

	if (!(m = (struct s_list *)allocator(sizeof(struct s_list))))
		return (NULL);
	if (!(m->content = (char *)allocator(len)))
	{
		deallocator(m);
		return (NULL);
	}
	m->content_size = len;
	if (!(*alst))
	{
		*alst = m;
		m->next = NULL;
		return (*alst);
	}
	m->next = *alst;
	*alst = m;
	return (*alst);
}
