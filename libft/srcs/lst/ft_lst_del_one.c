#include "list.h"

void	ft_lst_del_one(void **first, void *node, void (*f)(void*))
{
    t_gen_lst	*node_cast;
    t_gen_lst	*prev_node;

    node_cast = node;
    prev_node = *first;
    if (*first == node_cast)
        *first = node_cast->next;
    else
    {
        while (prev_node->next != node_cast)
            prev_node = prev_node->next;
        prev_node->next = node_cast->next;
    }
    if (f)
        (f)(node_cast);
    free(node_cast);
}

void		ft_dlst_del_one(void **first, void *node, void (*f)(void*))
{
    t_gen_dlst *node_cast = node;

    if (node_cast->prev)
        node_cast->prev->next = node_cast->next;
    if (node_cast->next)
        node_cast->next->prev = node_cast->prev;

    if (node_cast == *first)
        *first = node_cast->next;
    if (f)
        (f)(node_cast);
    free(node_cast);
}
