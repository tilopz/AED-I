#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINITO INT_MAX 
#define MAX_CIDADES 250 


int custo_pedagio[MAX_CIDADES][MAX_CIDADES];

void dijkstra(int N, int origem, int *distancia) {
    int visitado[MAX_CIDADES];  
    int i, u, v, min_dist;

    for (i = 0; i < N; i++) {
        distancia[i] = INFINITO;
        visitado[i] = 0;
    }
    distancia[origem] = 0;

    for (i = 0; i < N; i++) {

        min_dist = INFINITO;
        u = -1; 

        for (v = 0; v < N; v++) {
            if (visitado[v] == 0 && distancia[v] < min_dist) {
                min_dist = distancia[v];
                u = v;
            }
        }

        if (u == -1) break;
        visitado[u] = 1;

        for (v = 0; v < N; v++) {
            int custo_aresta = custo_pedagio[u][v];

            if (custo_aresta != INFINITO) {
                if (distancia[u] != INFINITO && (long long)distancia[u] + custo_aresta < distancia[v]) {
                    distancia[v] = distancia[u] + custo_aresta;
                }
            }
        }
    }
}

int main() {
    int N, M, C, K;

    while (scanf("%d %d %d %d", &N, &M, &C, &K) == 4 && (N != 0 || M != 0 || C != 0 || K != 0)) {
        int i, j;
        
        // 1. Inicializa a matriz com INFINITO
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                custo_pedagio[i][j] = (i == j) ? 0 : INFINITO;
            }
        }

        for (i = 0; i < M; i++) {
            int U, V, P; 
            if (scanf("%d %d %d", &U, &V, &P) != 3) break;

            if (custo_pedagio[U][V] > P) {
                custo_pedagio[U][V] = P;
            }
            if (custo_pedagio[V][U] > P) {
                custo_pedagio[V][U] = P;
            }
        }

        for (i = 0; i < C - 1; i++) {
            int destino_obrigatorio = i + 1;
            
            for (j = 0; j < N; j++) {
                if (j != destino_obrigatorio) {
                    custo_pedagio[i][j] = INFINITO;
                }
            }
        }
        int distancias[MAX_CIDADES];
        dijkstra(N, K, distancias); 
        int destino = C - 1;
        printf("%d\n", distancias[destino]);
    }
    
    return 0;
}