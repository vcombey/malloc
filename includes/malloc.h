#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <sys/mman.h>
#include "malloc.h"
#include "libft.h"
#include <stdio.h>

extern struct zones g_zones;

void ft_free(void *ptr);
void *ft_malloc(size_t size);
void *ft_realloc(void *ptr, size_t size);
void show_alloc_mem(void);


#define LITTLE_BLOCK = 32
/* Litlle_zone_size must be > 100 * little_max an a multiple of 4096 */
#define LITTLE_ZONE_SIZE = (128 * LITTLE_BLOCK)
#define LITTLE_MAX = (31 * LITTLE_BLOCK)

#define MEDIUM_BLOCK = (33 * LITTLE_BLOCK)
#define MEDIUM_ZONE_SIZE = (128 * MEDIUM_BLOCK)
/* medium_zone_size must be > 100 * little_max an a multiple of 4096 */
#define MEDIUM_MAX = (31 * MEDIUM_BLOCK)

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
/* 16 */
struct  chunk {
    void    *parent;
    size_t  size_block;
}

enum    e_zone_type {
    LITTLE = 0,
    MEDIUM,
    LARGE
}

/* 32 */
struct  zone_reference {
    __uint128_t     allocated_chunks; //bitmask of allocated area
    void            *ptr; //memory pointer
    uint8_t         free_space; //free space in zone
}

struct  priority_queue {
    size_t                  lenght;
    size_t                  size;
    // a vector of size size
    struct zone_reference   *vec;
}

struct  zones {
    struct priority_queue     little_heap;
    struct priority_queue     medium_heap;
    size_t                    page_size;
    bool                      init;
}
