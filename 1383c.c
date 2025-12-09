#include <stdio.h>
#include <stdlib.h>

int verifica_lin (int matriz[9][9], int linha){
    int i, j, n, lista_num[10];
    for (j = 0; j < 10; j++){
        lista_num[j] = 0;
    }
    for (i = 0; i < 9; i++){
        n = matriz[linha][i];
        if (n < 1 || n > 9 || lista_num[n]) return 0;
        lista_num[n] = 1;
    }
    return 1;
}

int verifica_col (int matriz[9][9], int coluna){
    int i, j, n, lista_num[10];
    for (j = 0; j < 10; j++){
        lista_num[j] = 0;
    }
    for (i = 0; i < 9; i++){
        n = matriz[i][coluna];
        if (n < 1 || n > 9 || lista_num[n]) return 0;
        lista_num[n] = 1;
    }
    return 1;
}

int verifica_quadrado (int matriz[9][9], int linha, int coluna){
    int i, j, k, n, lista_num[10];
    for (k = 0; k < 10; k++){
        lista_num[k] = 0;
    }
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            n = matriz[linha + i][coluna + j];
            if (n < 1 || n > 9 || lista_num[n]) return 0;
            lista_num[n] = 1;
        }
    }
    return 1;
}

int verifica_sudoku (int matriz[9][9]){
    int i, j;
    for (i = 0; i < 9; i++) {
        if (!verifica_lin(matriz, i) || !verifica_col(matriz, i)) return 0;
    }
    
    for (i = 0; i < 9; i = i + 3){
        for (j = 0; j < 9; j = j + 3){
            if (!verifica_quadrado(matriz, i, j)) return 0;
        }
    }
    return 1;
}

int main() {
    
    int n, i, j, k;
    if (scanf("%d", &n) != 1) return 1;

    for (k = 1; k <= n; k++){
        int (*matriz)[9] = (int (*)[9])malloc(9 * 9 * sizeof(int)); 
        
        if (matriz == NULL) {
            fprintf(stderr, "Erro de alocação de memória.\n");
            return 1;
        }
        
        for (i = 0; i < 9; i++){
            for (j = 0; j < 9; j++){
                if (scanf("%d", &matriz[i][j]) != 1) {
                    free(matriz);
                    return 1;
                }
            }
        }

        printf ("Instancia %d\n", k);

        if(verifica_sudoku(matriz)){
            printf("SIM\n");
        }
        else{
            printf("NAO\n");
        }

        printf("\n"); 

        free(matriz);
    }
    
    return 0;
}