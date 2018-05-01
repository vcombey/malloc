#include "malloc.h"
#include "internal_malloc.h"

void    print_binary(__uint128_t nb) {
    for (int i = 0; i < 128; i++)
    {
        printf("%i", (int)(nb % 2));
        nb >>= 1;
    }
    printf("\n");
}
