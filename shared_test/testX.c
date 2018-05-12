#include "malloc.h"
#include <time.h>
#define MAX (31 * 33 * 32 * 2)

#define malloc ft_malloc
#define free ft_free
#define realloc ft_realloc

int main()
{
	void *tab[1000];
	int nb = 0;

	srand(time(NULL));

	for(int i=0; i<10000; i++){
		nb = rand() % MAX;

		printf("bonjour %i\n", i);
		if (nb % 3 == 0)
			tab[nb % 1000] = malloc(nb);
		else if (nb % 3 == 1)
			free(tab[nb % 1000]);
		else if (nb % 3 == 2)
			tab[nb % 1000] = realloc(tab[nb % 1000], nb);
	}
}
