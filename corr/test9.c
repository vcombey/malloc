
#include "malloc.h"

int main()
{
	void	*addr = malloc(1024);
	free(addr);
	free(addr);
}
