#include "chained_tools.h"

static struct s_list	*invert(struct s_list **alst, struct s_list *ptr)
{
	if (!ptr->next)
		*alst = ptr;
	else
		invert(alst, ptr->next)->next = ptr;
	return (ptr);
}

struct s_list			*lst_invert_rec(struct s_list **alst)
{
	invert(alst, *alst)->next = NULL;
	return (*alst);
}
