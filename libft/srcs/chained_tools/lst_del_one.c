#include "chained_tools.h"

void	lst_del_one(struct s_list **alst, void (*del)(void *, size_t),
		void (*deallocator)(void *))
{
	del((*alst)->content, (*alst)->content_size);
	deallocator(*alst);
	*alst = NULL;
}
