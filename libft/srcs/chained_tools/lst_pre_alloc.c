#include "chained_tools.h"

struct s_list	*lst_pre_alloc(
		struct s_list **alst,
		size_t len,
		void *(*allocator)(size_t),
		void (*deallocator)(void *))
{
	struct s_list *m;

	if (!(m = (struct s_list *)allocator(sizeof(struct s_list))))
		return (NULL);
	if (!(m->content = (char *)allocator(len)))
	{
		deallocator(m);
		return (NULL);
	}
	m->content_size = len;
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
