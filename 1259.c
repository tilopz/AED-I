#include <stdio.h>
#include <stdlib.h>

int compara_pares_impares(const void *a, const void *b) {
    int num_a = *(int*)a;
    int num_b = *(int*)b;

    int par_a = num_a % 2 == 0;
    int par_b = num_b % 2 == 0;

    if (par_a && !par_b) {
        return -1;
    }
    if (!par_a && par_b) {
        return 1;
    }
    if (par_a && par_b) {
        return num_a - num_b;
    }
    if (!par_a && !par_b) {
        return num_b - num_a;
    }
    return 0;
}


int main() {
    int N;
    if (scanf("%d", &N) != 1) return 1;

    int *numeros = (int*)malloc(N * sizeof(int));
    if (numeros == NULL) return 1;

    for (int i = 0; i < N; i++) {
        if (scanf("%d", &numeros[i]) != 1) {
            free(numeros);
            return 1;
        }
    }

    qsort(numeros, N, sizeof(int), compara_pares_impares);

    for (int i = 0; i < N; i++) {
        printf("%d\n", numeros[i]);
    }

    free(numeros);

    return 0;
}