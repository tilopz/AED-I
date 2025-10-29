#include <stdio.h>

void Insercao (int n, int v[]){
    int i, j, x;
    for (j = 1; j < n; j++){
        x = v[j];
        for (i = j-1; i >= 0 && v[i] > x; i--){
            v[i+1] = v[i];
        }
        v[i+1] = x;
    }
}

int main() {
    int NC, i;
    scanf("%d", &NC);
    if (NC >= 100){
        printf("Erro na quantidade de casos\n");
        return 1;
    }

    for (i = 0; i < NC; i++){
        int N, j;
        scanf("%d", &N);
        if (N <= 1 || N > 3000000){
            printf("Erro no tamanho do vetor\n");
            return 1;
        }
        int v[N];
        for (j = 0; j < N; j++){
            scanf("%d", &v[j]);
            if (v[j] < 20 || v[j] > 230){
                printf("Erro na altura\n");
                return 1;
            }
        }
        Insercao(N, v);
        for (j = 0; j < N; j++){
            printf("%d ", v[j]);
        }
        printf("\n");
    }
    return 0;
}