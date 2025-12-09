#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10000
#define TAM_FILA 20000


int distancias[MAX_N + 1];
int fila[TAM_FILA];

int inverte_numero(int n) {
    int invertido = 0;
    while (n > 0) {
        invertido = invertido * 10 + (n % 10);
        n /= 10;
    }
    return invertido;
}

int busca_largura(int a, int b) {
    if (a == b) return 0;
    memset(distancias, -1, sizeof(distancias));
    int cabeca = 0;
    int cauda = 0; 
    
    fila[cauda++] = a;
    distancias[a] = 0;

    while (cabeca < cauda) {
        int u = fila[cabeca++];
        int dist_u = distancias[u];
        int v_soma = u + 1;
        if (v_soma <= MAX_N && distancias[v_soma] == -1) {
            if (v_soma == b) return dist_u + 1;
            distancias[v_soma] = dist_u + 1;
            fila[cauda++] = v_soma;
        }
        int v_inverte = inverte_numero(u);
        if (distancias[v_inverte] == -1) {
            if (v_inverte == b) return dist_u + 1;
            distancias[v_inverte] = dist_u + 1;
            fila[cauda++] = v_inverte;
        }
    }
    return -1; 
}

int main() {
    int T, i;
    if (scanf("%d", &T) != 1) return 1;
    for (i = 0; i < T; i++){
        int a, b;
        if (scanf("%d %d", &a, &b) != 2) return 1;
        printf("%d\n", busca_largura(a, b));
    }
    return 0;
}