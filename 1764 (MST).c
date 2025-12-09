#include <stdio.h>
#include <stdlib.h>

#define MAX_CIDADES 50000
#define MAX_ARESTAS 40000

typedef struct {
    int cid_u, cid_v; 
    int custo;    
} rota;

int conj_pai[MAX_CIDADES];

int compara_rotas(const void *a, const void *b) {
    return ((rota *)a)->custo - ((rota *)b)->custo;
}

void inicializa_conjunto(int N) {
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

long long kruskal(int N, rota rotas[], int num_arestas) {
    inicializa_conjunto(N);

    qsort(rotas, num_arestas, sizeof(rota), compara_rotas);
    
    long long custo_total_min = 0;
    int num_rotas_agm = 0;

    for (int i = 0; i < num_arestas; i++) {
        int u = rotas[i].cid_u;
        int v = rotas[i].cid_v;
        int custo = rotas[i].custo;

        if (encontra_conjunto(u) != encontra_conjunto(v)) {
            custo_total_min += custo;
            une_conjunto(u, v);
            num_rotas_agm++;

            if (num_rotas_agm == N - 1) {
                break;
            }
        }
    }
    
    return custo_total_min;
}

int main() {
    int m_cidades, n_caminhos; 
    rota rotas[MAX_ARESTAS];

    while (scanf("%d %d", &m_cidades, &n_caminhos) == 2 && (m_cidades != 0 || n_caminhos != 0)) {

        for (int i = 0; i < n_caminhos; i++) {
            int x, y, z;
            if (scanf("%d %d %d", &x, &y, &z) != 3) break;
            
            rotas[i].cid_u = x;
            rotas[i].cid_v = y;
            rotas[i].custo = z;
        }
        
        long long resultado = kruskal(m_cidades, rotas, n_caminhos);

        printf("%lld\n", resultado);
    }

    return 0;
}