#include "list.h"

/*
** Get the n'th node of the list from where we are. first is node 0
** if n < 0, -1 is the last node and so on
*/

void		*ft_lst_get_n(void *first, int n)
{
	t_gen_lst	*first_cast;

	first_cast = first;
	if (n < 0)
		n = ft_lst_len(first) - n;
	if (n < 0)
		return (NULL);
	while (first_cast && n)
	{
		n--;
		first_cast = first_cast->next;
	}
	return (first_cast);
}

void        *ft_dlst_get_n(void *first, int n)
{
    return ft_lst_get_n(first, n);
}
