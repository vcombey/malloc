/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_internal_header.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmickael <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 14:13:04 by bmickael          #+#    #+#             */
/*   Updated: 2017/03/24 07:10:12 by bmickael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_INTERNAL_HEADER_H
# define BTREE_INTERNAL_HEADER_H

# include "btree.h"

# include <stdlib.h>
# include <errno.h>
# include <stdint.h>

struct s_node	*btree_internal_insert_node(
		struct s_node **root,
		struct s_node *new,
		int (*cmpf)(struct s_node *, struct s_node *));

struct s_node	*btree_internal_trash_node(
		struct s_node *node,
		struct s_node **root,
		struct s_node **sibling);

void			apply_insert_strategy(struct s_node *new);

void			apply_delete_strategy(
		struct s_node *trash,
		struct s_node **root,
		struct s_node *sibling);

/*
** Internal use.
*/

void			btree_rotate_right(struct s_node *n);
void			btree_rotate_left(struct s_node *n);

struct s_node	*btree_get_parent(struct s_node *n);
struct s_node	*btree_get_grandparent(struct s_node *n);
struct s_node	*btree_get_sibling(struct s_node *n);
struct s_node	*btree_get_uncle(struct s_node *n);

void			minor_rotations_case(
		struct s_node *sibling,
		struct s_node **root);

void			major_rotations_case(
		struct s_node *sibling,
		struct s_node **root);

#endif
