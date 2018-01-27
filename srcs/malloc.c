#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include "malloc.h"
#include "libft.h"

#include <stdio.h>

#define LITTLE_MAX 10
/* Litlle_zone_size must be > 100 * little_max an a multiple of 4096 */
#define LITTLE_ZONE_SIZE 4096

#define MEDIUM_MAX 4096
/* medium_zone_size must be > 100 * little_max an a multiple of 4096 */
#define MEDIUM_ZONE_SIZE 101 * MEDIUM_MAX

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
    char            free;
    size_t          len;
};

struct s_mem *g_medium_mem = NULL;
struct s_mem *g_large_mem = NULL;

void    ft_free(void *ptr) {
    if (ptr == NULL)
        return ;

    if (size > LITTLE_MAX && size < MEDIUM_MAX) {
    }
    if (size > MEDIUM_MAX) {
        struct s_mem *tmp = g_large_mem;
        struct s_mem *prev = g_large_mem;

        while (tmp) {
            if (tmp == ptr - sizeof(struct s_mem)) {
                ft_putstr_fd("munmap\n", 2);
                prev->next = tmp->next;
                if (tmp == g_large_mem) {
                    g_large_mem = NULL;
                }
                if (munmap(tmp, tmp->len) == -1)
                    perror("mmunmap err: ");
                break ;
            }
            prev = tmp;
            tmp = tmp->next;
        }
    }
}

void    display(struct s_mem *elem) {
    char    info_mem[50];
    sprintf(info_mem, "%p - %p : %zu octets\n", elem, elem + elem->len, elem->len);
    ft_putstr_fd((char*)info_mem, 2);
}

void    *ft_realloc(void *ptr, size_t size) {
    ft_putstr_fd("realloc\n", 2);
    ft_free(ptr);
    ft_malloc(size);
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
}

void    *ft_malloc(size_t size) {
    ft_putstr_fd("malloc\n", 2);

    if (size > LITTLE_MAX && size < MEDIUM_MAX) {
    }
    if (size > MEDIUM_MAX) {
        void    *addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        struct s_mem *m = addr;
        m->len = size;
        display(m);
        ft_genlst_pushback((void*)&g_large_mem, m);
        return (addr + sizeof(struct s_mem));
    }
}

void show_alloc_mem(void) {
    struct s_mem *tmp = g_large_mem;

    ft_putstr_fd("show_alloc_mem\n", 2);
    while (tmp) {
        display(tmp);
        tmp = tmp->next;
    }
    return ;
}
