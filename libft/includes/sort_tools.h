/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tools.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 17:01:44 by vcombey           #+#    #+#             */
/*   Updated: 2018/06/17 17:01:48 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_TOOLS_H
# define SORT_TOOLS_H

# include <stdlib.h>
# include <errno.h>

# include "chained_tools.h"
# include "custom_allocator.h"

# define FALSE		0
# define TRUE		1

struct	s_info
{
	int			offset;
	int			(*cmp)(void *, void *);
};

int		fusion_merge_chain_list(
		struct s_list *lst,
		int (*cmp)(void *, void *),
		struct s_custom_memory_fn *mem);

int		fusion_merge_tab(
		void ***t1,
		int len,
		int (*cmp)(void *, void *),
		struct s_custom_memory_fn *mem);

#endif
