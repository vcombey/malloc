#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include "malloc.h"
#include "libft.h"

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

struct s_mem
{
    struct s_mem    *next;
    size_t          len;
};

struct s_mem *g_mem = NULL;

void    free(void *ptr) {
    struct s_mem *tmp = g_mem;
    struct s_mem *prev = g_mem;

    if (ptr == NULL)
        return ;
    while (tmp) {
        if (tmp == ptr - sizeof(struct s_mem)) {
            write(2, "munmap\n", 8);
            prev->next = tmp->next;
            if (munmap(tmp, tmp->len) == -1)
                perror("mmunmap err: ");
            break ;
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return ;
}

void    *realloc(void *ptr, size_t size) {
    write(2, "realoc\n", 8);
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);

    
}

void    *malloc(size_t size) {
    write(2, "malloc\n", 8);

    void    *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    struct s_mem *m = addr;
    m->len = size;
    ft_genlst_pushback(&g_mem, m);
    return (addr + sizeof(struct s_mem));
}

void show_alloc_mem(void) {
    struct s_mem *tmp = g_mem;

    write(2, "show_alloc_mem\n", 8);
    while (tmp) {
        printf("%p - %p : %zu octets", tmp, tmp + tmp->len, tmp->len);
        tmp = tmp->next;
    }
    return ;
}
