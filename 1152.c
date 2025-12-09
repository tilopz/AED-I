#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cid_u, cid_v;
    int custo;
} rota;

int *conj_pai;


int compara_rotas(const void *a, const void *b) {
    return ((rota *)a)->custo - ((rota *)b)->custo;
}

void inicializa_conjunto(int N) {
    conj_pai = (int*)malloc(N * sizeof(int));
    if (conj_pai == NULL) exit(1);
    
    for (int i = 0; i < N; i++) {
        conj_pai[i] = i; 
    }
}

int encontra_conjunto(int i) { 
    if (conj_pai[i] == i) {
        return i;
    }
    return conj_pai[i] = encontra_conjunto(conj_pai[i]); 
}

void une_conjunto(int i, int j) {
    int raiz_i = encontra_conjunto(i);
    int raiz_j = encontra_conjunto(j);
    if (raiz_i != raiz_j) {
        conj_pai[raiz_i] = raiz_j;
    }
}

long long kruskal(int N, rota rotas[], int num_arestas, long long *custo_original) {
    long long custo_agm = 0;
    int num_rotas_agm = 0;
    inicializa_conjunto(N);
    *custo_original = 0;

    for (int i = 0; i < num_arestas; i++) {
        *custo_original += rotas[i].custo;
    }

    qsort(rotas, num_arestas, sizeof(rota), compara_rotas);

    for (int i = 0; i < num_arestas; i++) {
        int u = rotas[i].cid_u;
        int v = rotas[i].cid_v;
        int custo = rotas[i].custo;
        if (encontra_conjunto(u) != encontra_conjunto(v)) {
            custo_agm += custo;
            une_conjunto(u, v);
            num_rotas_agm++;
            if (num_rotas_agm == N - 1) {
                break;
            }
        }
    }

    free(conj_pai);
    
    return custo_agm;
}

int main() {
    int M_cidades, N_caminhos; 
    while (scanf("%d %d", &M_cidades, &N_caminhos) == 2 && (M_cidades != 0 || N_caminhos != 0)) {

        rota *rotas = (rota*)malloc(N_caminhos * sizeof(rota));
        if (rotas == NULL) return 1;
        for (int i = 0; i < N_caminhos; i++) {
            int x, y, z;
            if (scanf("%d %d %d", &x, &y, &z) != 3) {
                free(rotas);
                return 1;
            }
            rotas[i].cid_u = x;
            rotas[i].cid_v = y;
            rotas[i].custo = z;
        }
        
        long long custo_original;

        long long custo_agm = kruskal(M_cidades, rotas, N_caminhos, &custo_original);
        
        long long economia = custo_original - custo_agm;
        
        printf("%lld\n", economia);
        free(rotas);
    }

    return 0;
}