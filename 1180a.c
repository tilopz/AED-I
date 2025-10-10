#include <stdio.h>

int main() {

    int N;
    scanf("%d", &N);
    if (N < 1 || N > 1000){
        printf("Erro no tamanho do vetor \n");
        return 1;
    }

    int X[N], i;
    int menor, posicao;
    
    scanf("%d", &X[0]);
    menor = X[0];
    posicao = 0;

    for (i = 1; i < N; i++){
        scanf("%d", &X[i]);
        if(X[i] < menor){
            menor = X[i];
            posicao = i;
        }
    }

    printf("Menor valor: %d \n", menor);
    printf("Posicao: %d \n", posicao);

    return 0;
}