#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include "malloc.h"
#include "libft.h"

#include <stdio.h>

/* 128 * LITTLE_BLOCK = LITTLE_ZONE_SIZE */
/* LITTLE_MAX = 31 * LITTLE_BLOCK */

/* MEDIUM_BLOCK = 33 * LITTLE_MAX */
/* 128 * MEDIUM_BLOCK = MEDIUM_ZONE_SIZE */
/* MEDIUM_MAX = 31 * MEDIUM_BLOCK */

/* MEDIUM_BLOCK > 1040 */

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

struct dlst_mem
{
    struct dlst_mem    *next;
    struct dlst_mem    *prev;
    char            free;
    size_t          len;
};

struct dlst_mem *g_medium_mem = NULL;
struct dlst_mem *g_large_mem = NULL;

void    ft_free(void *ptr) {
    if (ptr == NULL)
        return ;

    struct dlst_mem *tmp = g_large_mem;
    struct dlst_mem *prev = g_large_mem;

    while (tmp) {
        if (tmp == ptr - sizeof(struct dlst_mem)) {
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

void    display(struct dlst_mem *elem) {
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

/*    if (size > LITTLE_MAX && size < MEDIUM_MAX) {
    }
    if (size > MEDIUM_MAX) {
    */
        void    *addr = mmap(NULL, size + sizeof(struct dlst_mem), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        struct dlst_mem *m = addr;
        m->len = size;
        display(m);
        ft_dlst_pushback((void*)&g_large_mem, m);
        return (addr + sizeof(struct dlst_mem));
    return NULL;
}

void show_alloc_mem(void) {
    struct dlst_mem *tmp = g_large_mem;

    ft_putstr_fd("show_alloc_mem\n", 2);
    while (tmp) {
        display(tmp);
        tmp = tmp->next;
    }
    return ;
}
