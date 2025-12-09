#include <stdio.h>
#include <stdlib.h>

typedef struct cel {
    int vizinho;
    struct cel *prox;
} celula;

struct grafo {
    int V;
    int A;
    celula **adj;
};
typedef struct grafo *Grafo;

Grafo grafoinic (int v){
    Grafo g = malloc(sizeof *g);
    if (g == NULL) exit(1);
    g->V = v;
    g->A = 0;
    g->adj = (celula **)calloc(v, sizeof(celula *)); 
    if (g->adj == NULL) exit(1);
    
    return g;
}

void grafoadic (Grafo g, int a, int b){
    celula *novo = (celula *)malloc(sizeof(celula));
    if (novo == NULL) exit(1);
    novo->vizinho = b;
    novo->prox = g->adj[a];
    g->adj[a] = novo;
    g->A++;
}

int tem_ciclo_recursao(Grafo g, int u, int *estado) {
    estado[u] = 1;
    celula *p = g->adj[u];
    while (p != NULL) {
        int v = p->vizinho;
        
        if (estado[v] == 1) {
            return 1;
        }
        
        if (estado[v] == 0) {
            if (tem_ciclo_recursao(g, v, estado)) {
                return 1;
            }
        }
        p = p->prox;
    }
    
    estado[u] = 2;
    return 0;
}

int tem_ciclo(Grafo g) {
    int *estado = (int *)calloc(g->V, sizeof(int));
    if (estado == NULL) exit(1);

    for (int v = 0; v < g->V; v++) {
        if (estado[v] == 0) {
            if (tem_ciclo_recursao(g, v, estado)) {
                free(estado);
                return 1;
            }
        }
    }
    
    free(estado);
    return 0;
}

void grafo_libera(Grafo g) {
    for (int i = 0; i < g->V; i++) {
        celula *p = g->adj[i];
        while (p != NULL) {
            celula *temp = p;
            p = p->prox;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}

int main() {
    int T;
    
    if (scanf("%d", &T) != 1) return 0;
    
    for (int i = 0; i < T; i++){
        int N, M;
        Grafo g;
        
        if (scanf("%d %d", &N, &M) != 2) break;
        
        g = grafoinic(N);
        
        for (int j = 0; j < M; j++){
            int A, B;
            if (scanf("%d %d", &A, &B) != 2) break;
            grafoadic(g, A - 1, B - 1);
        }
        
        if (tem_ciclo(g)) {
            printf("SIM\n");
        } else {
            printf("NAO\n");
        }
        
        grafo_libera(g);
    }
    
    return 0;
}