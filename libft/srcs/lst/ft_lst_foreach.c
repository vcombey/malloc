#include "list.h"

void	ft_lst_foreach(void *start, void *end, void (*f)(void*))
{
    t_gen_lst	*start_cast;

    start_cast = start;
    while (start_cast != end)
    {
        (*f)(start_cast);
        start_cast = start_cast->next;
    }
}

void	ft_dlst_foreach(void *start, void *end, void (*f)(void*), int order)
{
    t_gen_dlst	*start_cast;

    start_cast = start;
    while (start_cast != end)
    {
        (*f)(start_cast);
        if (order > 0)
            start_cast = start_cast->next;
        else if (order < 0)
            start_cast = start_cast->prev;
    }
}
