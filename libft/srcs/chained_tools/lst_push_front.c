#include "chained_tools.h"

struct s_list	*lst_push_front(
		struct s_list **alst,
		void *data,
		size_t len,
		void *(*allocator)(size_t))
{
	struct s_list *m;

	if (!(m = lst_create_elem(data, len, allocator)))
		return (NULL);
	if (!(*alst))
	{
		*alst = m;
		m->next = NULL;
		return (*alst);
	}
	m->next = *alst;
	*alst = m;
	return (*alst);
}
