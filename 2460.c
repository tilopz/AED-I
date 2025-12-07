#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    int i, pessoa;
    
    if (scanf("%d", &n) != 1 || n < 1) return 1;

    int *fila_original = (int*) malloc(n * sizeof(int));
    if (fila_original == NULL) {
        printf("Erro de alocação!\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        if (scanf("%d", &fila_original[i]) != 1) {
            free(fila_original);
            return 1;
        }
    }

    if (scanf("%d", &m) != 1 || m < 0) {
        free(fila_original);
        return 1;
    }

    int max_id = 100001; 
    int *saidas = (int*) calloc(max_id, sizeof(int));
    
    if (saidas == NULL) {
        printf("Erro de alocação!\n");
        free(fila_original);
        return 1;
    }

    for (i = 0; i < m; i++) {
        if (scanf("%d", &pessoa) != 1) {
            free(fila_original);
            free(saidas);
            return 1;
        }
        if (pessoa < max_id) {
            saidas[pessoa] = 1;
        }
    }

    int primeiro = 1;
    for (i = 0; i < n; i++) {
        pessoa = fila_original[i];
        
        if (saidas[pessoa] == 0) {
            if (!primeiro) {
                printf(" ");
            }
            printf("%d", pessoa);
            primeiro = 0;
        }
    }
    printf("\n");

    free(fila_original);
    free(saidas);
    
    return 0;
}