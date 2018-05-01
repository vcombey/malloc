#ifndef INTERNAL_MALLOC_H
# define INTERNAL_MALLOC_H

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <sys/mman.h>
#include "malloc.h"
#include <stdio.h>
#include <stdbool.h>

extern struct zones g_zones;

#define LITTLE_HEADER_SIZE 32
#define LITTLE_BLOCK 32
/* Litlle_zone_size must be > 100 * little_max an a multiple of 4096 */
#define LITTLE_ZONE_SIZE (128 * LITTLE_BLOCK)
#define LITTLE_MAX (31 * LITTLE_BLOCK)

#define MEDIUM_HEADER_SIZE 128 * 8
#define MEDIUM_BLOCK (33 * LITTLE_BLOCK - 8) //
#define MEDIUM_ZONE_SIZE (128 * MEDIUM_BLOCK) + MEDIUM_HEADER_SIZE
/* medium_zone_size must be > 100 * little_max an a multiple of 4096 */
#define MEDIUM_MAX (31 * MEDIUM_BLOCK)


/* 100 < nb_block < 128 */
/* 100 < nb_block < 128 */
/* 100 < nb_block < 128 */
/* nb_block * MEDIUM_BLOCK + 16 */
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

enum    e_zone_type {
    LITTLE = 0,
    MEDIUM,
    LARGE
};

/* 24 */
struct  chunk {
    size_t              offset_zone_header;
    size_t              size_block;
    enum    e_zone_type zone_type;
};

/* 8 */
struct  header_zone {
    void                *parent;
};

/* 32 */
struct  zone_reference {
    __uint128_t             allocated_chunks; //bitmask of allocated area
    struct  header_zone     *ptr; //memory pointer
    uint8_t                 free_space; //free space in zone
};

struct  priority_queue {
    size_t                  lenght;
    size_t                  size;
    // a vector of size size
    struct zone_reference   *vec;
};

struct  zones {
    struct priority_queue     little_heap;
    struct priority_queue     medium_heap;
    size_t                    page_size;
    bool                      init;
};

void    unimplemented(char *mess);
int    add_priority_queue(struct priority_queue *pq, struct zone_reference new);
size_t  get_zone_size(enum e_zone_type zone_type);
size_t  get_zone_block(enum e_zone_type zone_type);
int     new_zone_reference(enum e_zone_type zone_type, struct zone_reference *new_zone_ref);
size_t  size_block_bitmask(size_t size_block);
int     offset_place_chunk(__uint128_t  allocated_chunks, size_t size_block, __uint128_t bitmask);
size_t  get_offset_zone_header(enum e_zone_type zone_type);
void    sift_down(struct priority_queue *pq, size_t pos);

#endif
