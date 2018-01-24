#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"

void    *malloc(size_t size) {
    write(2, "TROLOLO\n", 8);
    return NULL;
}
