#include "chained_tools.h"

struct s_list	*lst_create_elem(void *data, size_t len,
		void *(*allocator)(size_t))
{
	struct s_list *elmt;

	if (!(elmt = (struct s_list *)allocator(sizeof(struct s_list))))
		return (NULL);
	elmt->content = data;
	elmt->content_size = len;
	return (elmt);
}
