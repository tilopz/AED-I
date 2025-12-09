#include <stdio.h>

int main() {

    int N;
    
    if (scanf("%d", &N) != 1) return 1;
    
    int X[1000]; 
    int i;
    int menor;
    int posicao; 

    if (N < 1 || N > 1000){
        return 1;
    }

    if (scanf("%d", X) != 1) return 1;
    menor = *X;
    posicao = 0;

    for (i = 1; i < N; i++){
        if (scanf("%d", (X + i)) != 1) return 1;
        if(*(X + i) < menor){
            menor = *(X + i);
            posicao = i;
        }
    }

    printf("Menor valor: %d\n", menor);
    printf("Posicao: %d\n", posicao);

    return 0;
}