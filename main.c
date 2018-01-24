#include <stdio.h>

int main() {
    int *tab = malloc(100);
    *tab = 100;
    printf("%d", *tab);
}
