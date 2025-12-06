#include <stdio.h>
#include <stdlib.h>

void InsereEmHeap (int m, int v[]) {
    int f = m+1;
    while  (f > 1 && v[f/2] < v[f]) {
        int t = v[f/2]; v[f/2] = v[f]; v[f] = t;
        f = f/2;
    }
}

void SacodeHeap (int m, int v[]) {
    int t, f = 2;
    while /*X*/ (f <= m) {
        if (f < m && v[f] < v[f+1]) ++f;
        if (v[f/2] >= v[f]) break;
        t = v[f/2]; v[f/2] = v[f]; v[f] = t;
        f *= 2;
    }
}

void Heapsort (int n, int v[]) {
    int m;
    for (m = 1; m < n; m++) {
        InsereEmHeap (m, v);
    }
    for (m = n;  m > 1; m--) {
        int t = v[1]; v[1] = v[m]; v[m] = t;
        SacodeHeap (m-1, v);
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
       
        v = (int*) malloc((N +1) * sizeof(int));
        
        if (v == NULL) {
            printf("Erro de alocação!\n");
            return 1;
        }
        
        for (j = 1; j <= N; j++){
            scanf("%d", &v[j]);
            if (v[j] < 20 || v[j] > 230){
                printf("Erro na altura.\n");
                return 1;
            }
        }
        Heapsort(N, v);
        
        for (j = 1; j <= N; j++){
            printf("%d", v[j]);
            if (j < N) {
                printf(" ");
            }
        }
        printf("\n");

        free(v);
    }
    return 0;
}