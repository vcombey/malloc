/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:00:15 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/17 17:00:28 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "chained_tools.h"

static void		del_elem(void *elem, size_t size, void (*deallocator)(void *))
{
	(void)size;
	deallocator(elem);
	elem = NULL;
}

struct s_list	*lst_map(
	struct s_list *lst,
	struct s_list *(*f)(struct s_list *elem),
	void (*deallocator)(void *))
{
	struct s_list *current;
	struct s_list *elem;
	struct s_list *new_list;

	new_list = NULL;
	current = lst;
	while (current)
	{
		if (!(elem = f(current)))
		{
			lst_del(&new_list, &del_elem, deallocator);
			return (NULL);
		}
		lst_add(&new_list, elem);
		current = current->next;
	}
	return (lst_invert_it(&new_list));
}
