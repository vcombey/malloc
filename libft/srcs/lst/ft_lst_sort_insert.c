#include "list.h"

/*
void		ft_simple_lst_sort_insert(t_list **first, t_list *new_node, \
		int (*f)(t_list*, t_list*))
{
	int		first_ret;
	t_list	*curr_node;
	t_list	*old_node;

	curr_node = *first;
	old_node = curr_node;
	if (new_node)
	{
		if ((f)(*first, new_node) >= 0)
			ft_simple_lst_add(first, new_node);
		else
		{
			first_ret = (*f)(curr_node, new_node);
			while (curr_node && (f)(curr_node, new_node) == first_ret)
			{
				old_node = curr_node;
				curr_node = curr_node->next;
			}
			old_node->next = new_node;
			new_node->next = curr_node;
		}
	}
}
*/
