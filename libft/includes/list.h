/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:41 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:15:27 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef struct	s_gen_lst
{
	struct s_gen_lst	*next;
}				t_gen_lst;

typedef struct	s_gen_dlst
{
    struct s_gen_dlst	*next;
    struct s_gen_dlst	*prev;
}				t_gen_dlst;

void	ft_lst_rev(void **lst);

void	*ft_lst_return_if(void *start, int (*f)(void*));

void	*ft_dlst_return_if(void *start, int (*f)(void*), int order);

void	ft_lst_remove(void **first, void (*f)(void*));

void	ft_dlst_remove(void **first, void (*f)(void*));

void	*ft_dlst_pushback(void **first, void *new);

void	*ft_lst_pushback(void **first, void *new_node);

void	*ft_lst_pop(void **first);

size_t	ft_dlst_len(void *lst);

size_t	ft_lst_len(void *lst);

void	*ft_dlst_last(void *lst);

void	*ft_lst_last(void *lst);

void	ft_dlst_iteri(void *start, void *end, void (*f)(void*, size_t), int order);

void	ft_lst_iteri(void *start, void *end, void (*f)(void*, size_t));

void    *ft_dlst_get_n(void *first, int n);

void	*ft_lst_get_n(void *first, int n);

void	ft_dlst_foreach(void *start, void *end, void (*f)(void*), int order);

void	ft_lst_foreach(void *start, void *end, void (*f)(void*));

void	ft_dlst_for_n(void *start, int count, void (*f)(void*), int order);

void	ft_lst_for_n(void *start, int count, void (*f)(void*));

void	ft_dlst_del_one(void **first, void *node, void (*f)(void*));

void	ft_lst_del_one(void **first, void *node, void (*f)(void*));

void	ft_dlst_add(void **first, void *new);

void	ft_lst_add(void **first, void *new);

#endif
