#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;

    if (scanf("%d", &N) != 1) return 1;

    int *X = (int *)malloc(N * sizeof(int)); 

    if (X == NULL || N < 1){
        if (X != NULL) free(X);
        return 1;
    }
    
    int i;
    int menor;
    int posicao; 

    if (scanf("%d", X) != 1) {
        free(X);
        return 1;
    }

    menor = *X;
    posicao = 0;

    for (i = 1; i < N; i++){
        if (scanf("%d", (X + i)) != 1) break;
        if(*(X + i) < menor){
            menor = *(X + i);
            posicao = i;
        }
    }

    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", posicao);

    free(X);
    
    return 0;
}