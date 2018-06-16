#include "chained_tools.h"

void	lst_iter(struct s_list *lst, void (*f)(struct s_list *elem))
{
	struct s_list *current;

	current = lst;
	while (current)
	{
		f(current);
		current = current->next;
	}
}
