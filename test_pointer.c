int main() {
    int *tab = calloc(10, 1);

    tab[7] = 42;
    printf("%zu\n", &tab[7]);
    printf("%zu\n", (tab + 7 * sizeof(*tab)));
}
