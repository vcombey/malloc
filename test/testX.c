#include "malloc.h"
#define MEDIUM_MAX (31 * 33 * 32 * 2)
int main()
{

	int nombre_aleatoire = 0;
	srand(time(NULL)); // initialisation de rand
	for(int i=0; i<100000; i++){
		nombre_aleatoire = rand() % MEDIUM_MAX;
		printf("%d ",nombre_aleatoire);
	}
}
