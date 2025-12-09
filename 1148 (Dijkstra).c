#include <stdio.h>
#include <stdlib.h>

#define INFINITO 1000000 
#define MAX_PAISES 501

int custo[MAX_PAISES][MAX_PAISES];

void ajusta_custos(int N) {
    int i, j;
    for (i = 1; i <= N; i++) {
        for (j = 1; j <= N; j++) {
            if (custo[i][j] != INFINITO && custo[j][i] != INFINITO) {
                custo[i][j] = 0;
            }
        }
    }
}

int dijkstra(int N, int origem, int destino) {
    int distancia[MAX_PAISES];
    int visitado[MAX_PAISES];
    int i, u, v, min_dist;

    for (i = 1; i <= N; i++) {
        distancia[i] = INFINITO;
        visitado[i] = 0;
    }
    distancia[origem] = 0; 

    for (i = 1; i <= N; i++) {
        min_dist = INFINITO;
        u = -1;

        for (v = 1; v <= N; v++) {
            if (visitado[v] == 0 && distancia[v] <= min_dist) {
                min_dist = distancia[v];
                u = v;
            }
        }
        if (u == -1 || u == destino) {
            break;
        }
        visitado[u] = 1;
        for (v = 1; v <= N; v++) {
            if (visitado[v] == 0 && custo[u][v] != INFINITO) {
                if (distancia[u] != INFINITO && distancia[u] + custo[u][v] < distancia[v]) {
                    distancia[v] = distancia[u] + custo[u][v];
                }
            }
        }
    }
    return distancia[destino];
}

int main() {
    int N, E;
    while (scanf("%d %d", &N, &E) == 2 && (N != 0 || E != 0)) {
        int i, j, k;
        for (i = 1; i <= N; i++) {
            for (j = 1; j <= N; j++) {
                custo[i][j] = (i == j) ? 0 : INFINITO;
            }
        }

        for (k = 0; k < E; k++) {
            int X, Y, C;
            if (scanf("%d %d %d", &X, &Y, &C) != 3) return 1;
            custo[X][Y] = C;
        }

        ajusta_custos(N);

        int K;
        if (scanf("%d", &K) != 1) return 1;

        for (k = 0; k < K; k++) {
            int O, D;
            if (scanf("%d %d", &O, &D) != 2) return 1;

            int resultado = dijkstra(N, O, D);

            if (resultado == INFINITO) {
                printf("Nao e possivel entregar a carta\n");
            } else {
                printf("%d\n", resultado);
            }
        }
        printf("\n");
    }

    return 0;
}