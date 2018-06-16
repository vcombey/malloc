#include "chained_tools.h"

void	lst_add(struct s_list **alst, struct s_list *new)
{
	new->next = *alst;
	(*alst) = new;
}
