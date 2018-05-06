#include <stdio.h>
void recur() {
    int i;

    printf("stack i: %zu\n", (size_t)&i);
    printf("stack:   %zu\n", (size_t)recur);
    printf("2stack:   %zu\n", (size_t)&recur);

    return recur();
}

int main() {
    recur();
}
