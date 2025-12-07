#include <stdio.h>
#include <stdlib.h>

void ordenar(int n, int v[]){
    int i, j, x;
    for (j = 1; j < n; j++){
        x = v[j];
        for (i = j - 1; i >= 0 && v[i] < x; i--){ 
            v[i+1] = v[i];
        }
        v[i+1] = x;
    }
}

int main() {
    int NC, i;
    
    if (scanf("%d", &NC) != 1) return 1;
    
    for (i = 0; i < NC; i++){
        int n, j;
        int *original;
        int *ordenado;
        int contagem = 0;
        
        if (scanf("%d", &n) != 1) return 1;
        
        original = (int*) malloc(n * sizeof(int));
        ordenado = (int*) malloc(n * sizeof(int));
        
        if (original == NULL || ordenado == NULL) {
            printf("Erro de alocação!\n");
            if (original != NULL) free(original);
            if (ordenado != NULL) free(ordenado);
            return 1;
        }
        
        for (j = 0; j < n; j++){
            if (scanf("%d", &original[j]) != 1) {
                free(original);
                free(ordenado);
                return 1;
            }
            ordenado[j] = original[j];
        }
        
        ordenar(n, ordenado);
        
        for (j = 0; j < n; j++){
            if (original[j] == ordenado[j]){
                contagem++;
            }
        }
        
        printf("%d\n", contagem);

        free(original);
        free(ordenado);
    }
    
    return 0;
}