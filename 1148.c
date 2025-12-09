#include <stdio.h>
#include <stdlib.h>

#define INFINITO 1000000
#define MAX_PAISES 501

typedef struct {
    int origem;
    int destino;
    int custo;
} Aresta;

int custo_direto[MAX_PAISES][MAX_PAISES];

Aresta *lista_arestas;
int num_arestas_reais;

void ajusta_custos(int N, int E) {
    num_arestas_reais = 0;
    
    lista_arestas = (Aresta *)malloc(N * N * sizeof(Aresta)); 
    if (lista_arestas == NULL) exit(1);

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int custo_real = custo_direto[i][j];

            if (custo_real != INFINITO && i != j) { 
                if (custo_direto[j][i] != INFINITO) {
                    custo_real = 0;
                }
                lista_arestas[num_arestas_reais].origem = i;
                lista_arestas[num_arestas_reais].destino = j;
                lista_arestas[num_arestas_reais].custo = custo_real;
                num_arestas_reais++;
            }
        }
    }
}

int caminho_mais_curto(int N, int origem, int destino) {
    int distancia[MAX_PAISES];
    int i, j;

    for (i = 1; i <= N; i++) {
        distancia[i] = INFINITO;
    }
    distancia[origem] = 0;

    for (i = 1; i < N; i++) {
        int houve_mudanca = 0;
        
        for (j = 0; j < num_arestas_reais; j++) {
            int u = lista_arestas[j].origem;
            int v = lista_arestas[j].destino;
            int peso = lista_arestas[j].custo;

            if (distancia[u] != INFINITO && distancia[u] + peso < distancia[v]) {
                distancia[v] = distancia[u] + peso;
                houve_mudanca = 1;
            }
        }
        if (!houve_mudanca) break;
    }
    return distancia[destino];
}

int main() {
    int N, E;

    while (scanf("%d %d", &N, &E) == 2 && (N != 0 || E != 0)) {
        int i, j, k;
        for (i = 1; i <= N; i++) {
            for (j = 1; j <= N; j++) {
                custo_direto[i][j] = INFINITO;
            }
            custo_direto[i][i] = 0;
        }

        for (k = 0; k < E; k++) {
            int X, Y, C; 
            if (scanf("%d %d %d", &X, &Y, &C) != 3) return 1;
            custo_direto[X][Y] = C;
        }

        ajusta_custos(N, E);

        int K;
        if (scanf("%d", &K) != 1) return 1;

        for (k = 0; k < K; k++) {
            int O, D;
            if (scanf("%d %d", &O, &D) != 2) return 1;

            int resultado = caminho_mais_curto(N, O, D);

            if (resultado >= INFINITO) {
                printf("Nao e possivel entregar a carta\n");
            } else {
                printf("%d\n", resultado);
            }
        }
        printf("\n");
        
        free(lista_arestas);
    }

    return 0;
}