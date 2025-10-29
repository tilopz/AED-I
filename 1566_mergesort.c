#include <stdio.h>
#include <stdlib.h>

void Intercala (int p, int q, int r, int v[]) {
    int i, j, k, *w;
    w = malloc ((r-p) * sizeof (int));
    i = p; j = q; k = 0;
    while (i < q && j < r) {
        if (v[i] <= v[j]) w[k++] = v[i++];
        else w[k++] = v[j++];
    }
    while (i < q) w[k++] = v[i++];
    while (j < r) w[k++] = v[j++];
    for (i = p; i < r; i++) v[i] = w[i-p];
    free (w);
}

void Mergesort (int p, int r, int v[]) {
    if (p < r - 1) {
        int q = (p + r)/2;
        Mergesort (p, q, v);
        Mergesort (q, r, v);
        Intercala (p, q, r, v);
    }
}

int main() {
    int NC, i;
    scanf("%d", &NC);
    if (NC >= 100){
        printf("Erro na quantidade de casos.\n");
        return 1;
    }

    for (i = 0; i < NC; i++){
        int N, j;
        int *v;

        scanf("%d", &N);
        if (N <= 1 || N > 3000000){
            printf("Erro no tamanho do vetor.\n");
            return 1;
        }
        
        v = (int*) malloc(N * sizeof(int));

        if (v == NULL) {
            printf("Erro de alocação!\n");
            return 1;
        }

        for (j = 0; j < N; j++){
            scanf("%d", &v[j]);
            if (v[j] < 20 || v[j] > 230){
                printf("Erro na altura.\n");
                return 1;
            }
        }
        Mergesort(0, N, v);

        for (j = 0; j < N; j++){
            printf("%d ", v[j]);
        }
        printf("\n");

        free(v);
    }
    return 0;
}