#include "list.h"

void	*ft_lst_pop(void **first)
{
	t_gen_lst	*res;

	res = *first;
	if (*first)
		*first = ((t_gen_lst *)*first)->next;
	return (res);
}
