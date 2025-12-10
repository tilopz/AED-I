#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 2001
#define MAX_ARESTAS 200000

typedef struct Aresta {
    int vizinho;
    struct Aresta *prox;
} aresta;

typedef struct {
    aresta *adj[MAX_VERTICES];
    int visitado[MAX_VERTICES];
    int num_vertices;
} grafo;

void adiciona_aresta(grafo *g, int u, int v) {
    aresta *nova = (aresta *)malloc(sizeof(aresta));
    if (nova == NULL) exit(1);
    nova->vizinho = v;
    nova->prox = g->adj[u];
    g->adj[u] = nova;
}

void libera_memoria(grafo *g) {
    for (int i = 1; i <= g->num_vertices; i++) {
        aresta *p = g->adj[i];
        while (p != NULL) {
            aresta *temp = p;
            p = p->prox;
            free(temp);
        }
        g->adj[i] = NULL;
    }
}

void dfs(grafo *g, int u, int *contador_visitados) {
    g->visitado[u] = 1;
    (*contador_visitados)++;

    aresta *p = g->adj[u];
    while (p != NULL) {
        int v = p->vizinho;
        if (!g->visitado[v]) {
            dfs(g, v, contador_visitados);
        }
        p = p->prox;
    }
}

int eh_fortemente_conexo(int N, int M) {
    grafo g;
    grafo g_transposto;
    
    g.num_vertices = N;
    g_transposto.num_vertices = N;

    for (int i = 1; i <= N; i++) {
        g.adj[i] = NULL;
        g_transposto.adj[i] = NULL;
    }

    for (int i = 0; i < M; i++) {
        int V, W, P;
        if (scanf("%d %d %d", &V, &W, &P) != 3) {
            libera_memoria(&g);
            libera_memoria(&g_transposto);
            return 0;
        }

        adiciona_aresta(&g, V, W);

        if (P == 2) {
            adiciona_aresta(&g, W, V);
        }

        adiciona_aresta(&g_transposto, W, V);

        if (P == 2) {
            adiciona_aresta(&g_transposto, V, W);
        }
    }
    
    int visitados_g = 0;
    
    for (int i = 1; i <= N; i++) g.visitado[i] = 0;
    dfs(&g, 1, &visitados_g);

    if (visitados_g != N) {
        libera_memoria(&g);
        libera_memoria(&g_transposto);
        return 0;
    }
    
    int visitados_gt = 0;
    
    for (int i = 1; i <= N; i++) g_transposto.visitado[i] = 0;

    dfs(&g_transposto, 1, &visitados_gt);

    libera_memoria(&g);
    libera_memoria(&g_transposto);
    return visitados_gt == N;
}

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) == 2 && (N != 0 || M != 0)) {
        if (N == 0 || M == 0) {
            printf("1\n");
            continue;
        }
        if (eh_fortemente_conexo(N, M)) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
}