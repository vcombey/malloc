/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 13:38:18 by bmickael          #+#    #+#             */
/*   Updated: 2017/03/24 07:12:30 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree_internal_header.h"

/*
** Recursive descent.
*/

static void		insert_child(struct s_node *parent, struct s_node *new,
				int (*cmpf)(struct s_node *, struct s_node *))
{
	if (cmpf(new, parent) < 0)
	{
		if (!parent->left)
		{
			parent->left = new;
			new->parent = parent;
		}
		else
			insert_child(parent->left, new, cmpf);
	}
	else
	{
		if (!parent->right)
		{
			parent->right = new;
			new->parent = parent;
		}
		else
			insert_child(parent->right, new, cmpf);
	}
}

struct s_node	*btree_internal_insert_node(
		struct s_node **root,
		struct s_node *new,
		int (*cmpf)(struct s_node *, struct s_node *))
{
	new->left = NULL;
	new->right = NULL;
	if (!(*root))
	{
		*root = new;
		new->parent = NULL;
	}
	else
		insert_child(*root, new, cmpf);
	return (new);
}

struct s_node	*btree_insert_node(
		struct s_node **root,
		struct s_node *new,
		int (*cmpf)(struct s_node *, struct s_node *))
{
	if (root == NULL || new == NULL || cmpf == NULL || new->ptr_a == NULL)
		return (NULL);
	btree_internal_insert_node(root, new, cmpf);
	SET_BLACK(new);
	return (new);
}
