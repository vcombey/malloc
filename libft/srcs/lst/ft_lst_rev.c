#include "libft.h"

void	ft_lst_rev(void **lst)
{
	t_gen_lst *a;
	t_gen_lst *b;
	t_gen_lst *c;

	a = NULL;
	b = *lst;
	c = b->next;
	while (b)
	{
		b->next = a;
		a = b;
		b = c;
		if (c)
			c = c->next;
	}
	*lst = a;
}
