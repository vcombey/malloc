
#include "malloc.h"
#include <unistd.h>
#include <string.h>

#define M (1024 * 1024)

void print(char *s)
{
    write(1, s, strlen(s));
}

int main()
{
    char *addr1;
    char *addr2;
    char *addr3;

    addr1 = (char*)ft_malloc(16*M);
    strcpy(addr1, "Bonjours\n");
    print(addr1);
    addr2 = (char*)ft_malloc(16*M);
    addr3 = (char*)ft_realloc(addr1, 128*M);
    addr3[127*M] = 42;
    print(addr3);
    return (0);
} 
