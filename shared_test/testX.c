#include "malloc.h"
#include <time.h>
#define MAX (31 * 33 * 32 * 2)

#define malloc ft_malloc
#define free ft_free
#define realloc ft_realloc
#define TAB_SIZE 100

int main()
{
	void *tab[TAB_SIZE];
	int nb = 0;

	srand(time(NULL));

	for(int i=0; i<1000; i++){
		nb = rand() % MAX;

		printf("bonjour %i\n", i);
		if (nb % 3 == 0)
		{
			tab[nb % TAB_SIZE] = malloc(nb);
			if (tab[nb % TAB_SIZE] != NULL)
			{
				((char*)tab[nb % TAB_SIZE])[nb - 1] = '*';
				((char*)tab[nb % TAB_SIZE])[0] = '*';
			}
		}
		else if (nb % 3 == 1)
			free(tab[nb % TAB_SIZE]);
		else if (nb % 3 == 2)
		{
			tab[nb % TAB_SIZE] = realloc(tab[nb % TAB_SIZE], nb);
			if (tab[nb % TAB_SIZE] != NULL)
			{
				((char*)tab[nb % TAB_SIZE])[nb - 1] = '*';
				((char*)tab[nb % TAB_SIZE])[0] = '*';
			}
		}
	}
	show_alloc_mem();
}
