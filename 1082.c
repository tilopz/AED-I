#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int componente_atual[26];
int indice_comp; 

Grafo grafoinic (int v){
    Grafo g = malloc(sizeof *g);
    if (g == NULL) exit(1);
    g->V = v;
    g->A = 0;
    g->adj = (celula **)calloc(v, sizeof(celula *));
    if (g->adj == NULL) exit(1);
    
    return g;
}

void insere_aresta(Grafo g, int u, int v) {
    celula *novo = (celula *)malloc(sizeof(celula));
    if (novo == NULL) exit(1);
    novo->vizinho = v;
    novo->prox = g->adj[u];
    g->adj[u] = novo;
    novo = (celula *)malloc(sizeof(celula));
    if (novo == NULL) exit(1);
    novo->vizinho = u;
    novo->prox = g->adj[v];
    g->adj[v] = novo;
    g->A++;
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

int compara_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void dfs_componente(Grafo g, int u, int *visitado) {
    visitado[u] = 1;
    componente_atual[indice_comp++] = u;

    celula *p = g->adj[u];
    while (p != NULL) {
        int v = p->vizinho;
        
        if (visitado[v] == 0) {
            dfs_componente(g, v, visitado);
        }
        p = p->prox;
    }
}

void resolve_caso(int caso_id, Grafo g) {
    int num_componentes = 0;
    int *visitado = (int *)calloc(g->V, sizeof(int));
    if (visitado == NULL) exit(1);
    printf("Case #%d:\n", caso_id);

    for (int v = 0; v < g->V; v++) {
        if (visitado[v] == 0) {
            num_componentes++;
            indice_comp = 0;
            dfs_componente(g, v, visitado);
            qsort(componente_atual, indice_comp, sizeof(int), compara_int);
            for (int i = 0; i < indice_comp; i++) {
                printf("%c,", (char)('a' + componente_atual[i])); 
            }
            printf("\n");
        }
    }

    printf("%d connected components\n\n", num_componentes);

    free(visitado);
}

int main() {
    int T;
    
    if (scanf("%d", &T) != 1) return 0;
    
    for (int i = 1; i <= T; i++){
        int N, M;
        Grafo g;
        
        if (scanf("%d %d", &N, &M) != 2) break;
        
        g = grafoinic(N);
        
        for (int j = 0; j < M; j++){
            char A_char, B_char;
            if (scanf(" %c %c", &A_char, &B_char) != 2) break;
            int u = A_char - 'a';
            int v = B_char - 'a';

            insere_aresta(g, u, v);
        }
        resolve_caso(i, g);
        grafo_libera(g);
    }
    
    return 0;
}