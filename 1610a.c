#include <stdio.h>
#include <stdlib.h>

struct grafo {
    int V;
    int A;
    int **adj;
};
typedef struct grafo *Grafo;

static int **matrizint (int r, int s, int t){
    int **m = malloc (r * sizeof (int *));
    if (m == NULL) exit(1);
    for (int i = 0; i < r; ++i){
        m[i] = malloc (s * sizeof (int));
        if (m[i] == NULL) exit(1);
    }
    for (int i = 0; i < r; ++i){
        for (int j = 0; j < s; ++j){
            m[i][j] = t;
        }
    }
    return m;
}

Grafo grafoinic (int v){
    Grafo g = malloc (sizeof *g);
    if (g == NULL) exit(1);
    g->V = v;
    g->A = 0;
    g->adj = matrizint(v, v, 0); 
    return g;
}

void grafoadic (Grafo g, int a, int b){
    if (g->adj[a][b] == 0){
        g->adj[a][b] = 1;
        g->A++;
    }
}

void grafo_libera(Grafo g, int N) {
    for (int k = 0; k < N; k++) {
        free(g->adj[k]);
    }
    free(g->adj);
    free(g);
}

int tem_ciclo_r(Grafo g, int u, int *estado) {
    estado[u] = 1;
    for (int v = 0; v < g->V; v++) {
        if (g->adj[u][v] == 1) {
            if (estado[v] == 1) {
                return 1;
            }
            if (estado[v] == 0) {
                if (tem_ciclo_r(g, v, estado)) {
                    return 1;
                }
            }
        }
    }
    
    estado[u] = 2;
    return 0;
}

int tem_ciclo(Grafo g) {
    int *estado = (int *)calloc(g->V, sizeof(int));
    if (estado == NULL) exit(1);

    for (int v = 0; v < g->V; v++) {
        if (estado[v] == 0) {
            if (tem_ciclo_r(g, v, estado)) {
                free(estado);
                return 1;
            }
        }
    }
    free(estado);
    return 0;
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
        
        grafo_libera(g, N);
    }
    
    return 0;
}