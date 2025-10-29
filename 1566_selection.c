#include <stdio.h>
#include <stdlib.h>

void Selecao (int n, int v[]) {
    int i, j, min, x;
    for (i = 0; i < n-1; i++) {
        min = i;
        for (j = i+1; j < n; j++) {
            if (v[j] < v[min]) min = j;
        }
        x = v[i];
        v[i] = v[min];
        v[min] = x;
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
        Selecao(N, v);
        for (j = 0; j < N; j++){
            printf("%d ", v[j]);
        }
        printf("\n");

        free(v);
    }
    return 0;
}