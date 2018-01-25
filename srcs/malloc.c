#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "malloc.h"

#include <stdio.h>

const size_t n = 10;
const size_t N = 100 * n;
const size_t m = 100;
const size_t M = 100 * m;

/*
**
** “TINY” mallocs, from 1 to n bytes, will be stored in N bytes big zones.
** 
** “SMALL” mallocs, from (n+1) to m bytes, will be stored in M bytes big zones.
** 
** “LARGE” mallocs, fron (m+1) bytes and more, will be stored out of zone,
** which simply means with mmap(), they will be in a zone on their own.
**
*/

void    free(void *prt) {
    return ;
}

void    *realloc(void *ptr, size_t size) {
    write(2, "realoc\n", 8);
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
}

void    *malloc(size_t size) {
//    write(2, "tralala\n", 8);
//    printf("lol\n");
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    return NULL;
}

void show_alloc_mem(void) {
    write(2, "show_alloc_mem\n", 8);
}
