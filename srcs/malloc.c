#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "malloc.h"

void    free(void *prt) {
    return ;
}

void    *realloc(void *ptr, size_t size) {
    write(2, "realoc\n", 8);
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
}

void    *malloc(size_t size) {
//    write(2, "tralala\n", 8);
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    return NULL;
}
