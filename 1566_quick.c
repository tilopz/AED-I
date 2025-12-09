#include <stdio.h>
#include <stdlib.h>

void troca(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int particiona(int v[], int baixo, int alto) {
    int pivo = v[alto];
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (v[j] <= pivo) {
            i++;
            troca(&v[i], &v[j]);
        }
    }
    troca(&v[i + 1], &v[alto]);
    return (i + 1);
}


void quicksort(int v[], int baixo, int alto) {
    if (baixo < alto) {

        int pi = particiona(v, baixo, alto);

        quicksort(v, baixo, pi - 1);
        quicksort(v, pi + 1, alto);
    }
}


int main() {
    int NC, i;

    if (scanf("%d", &NC) != 1) return 1;


    for (i = 0; i < NC; i++){
        int N, j;
        int *v;

        if (scanf("%d", &N) != 1) continue; 

        v = (int*) malloc(N * sizeof(int));
        
        if (v == NULL) {
            return 1;
        }
        
        for (j = 0; j < N; j++){
            if (scanf("%d", &v[j]) != 1) break;
        }
        
        quicksort(v, 0, N - 1);
        
        for (j = 0; j < N; j++){
            printf("%d", v[j]);
            if (j < N - 1) {
                printf(" ");
            }
        }
        printf("\n");
        free(v);
    }
    return 0;
}