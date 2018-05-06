#include "malloc.h"

int main()
{
	ft_free((void*)8);
	ft_free((void*)16);
	ft_free((void*)0xffffff00);
}
