#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <sys/mman.h>
#include "malloc.h"
#include "libft.h"

#include <stdio.h>

#define TINY_MAX  32
/* tiny_zone_size must be > 100 * tiny_max an a multiple of 4096 */
#define TINY_ZONE_SIZE 4096

#define SMALL_MAX (1024 + 16)
/* small_zone_size must be > 100 * small_max an a multiple of 4096 */
#define SMALL_ZONE_SIZE SMALL_MAX * 128

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
/* 1024 * 1024 */
/* 16 */
struct  chunk {
    size_t  size;
    void    *parent;
}

/* 32 */
struct  page_reference {
    __uint128_t     allocated_chunks; //bitmask of allocated area
    void            *ptr;
    uint8_t         nb_free;
}

struct  priority_queue {
    size_t                  lenght;
    size_t                  size;
    struct page_reference   *vec;
}

struct  zones {
    struct priority_queue     tiny_tree;
    struct priority_queue     small_tree;
}
