
#include "malloc.h"

int main()
{
	void	*addr = malloc(1024);
	ft_free(addr);
	ft_free(addr);
}
