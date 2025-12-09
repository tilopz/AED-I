#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define infinito 1000000000
#define max_n 10001 

typedef struct {
    int destino;
    int custo;
    struct trecho *proximo;
} trecho;

trecho *adjacencia[max_n];

int distancias[max_n][2];

typedef struct {
    int custo;
    int cidade;
    int paridade;
} noh_heap;

noh_heap *heap_minimo;
int tamanho_heap;

void trocar(int i, int j) {
    noh_heap temp = heap_minimo[i];
    heap_minimo[i] = heap_minimo[j];
    heap_minimo[j] = temp;
}

void descer_heap(int i) {
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < tamanho_heap && heap_minimo[esquerda].custo < heap_minimo[menor].custo)
        menor = esquerda;

    if (direita < tamanho_heap && heap_minimo[direita].custo < heap_minimo[menor].custo)
        menor = direita;

    if (menor != i) {
        trocar(i, menor);
        descer_heap(menor);
    }
}

void subir_heap(int i) {
    while (i > 0 && heap_minimo[(i - 1) / 2].custo > heap_minimo[i].custo) {
        trocar(i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

void inserir_heap(int custo, int cidade, int paridade) {
    if (tamanho_heap >= max_n * 2) return;
    heap_minimo[tamanho_heap].custo = custo;
    heap_minimo[tamanho_heap].cidade = cidade;
    heap_minimo[tamanho_heap].paridade = paridade;
    tamanho_heap++;
    subir_heap(tamanho_heap - 1);
}

noh_heap extrair_minimo() {
    if (tamanho_heap == 0) {
        noh_heap vazio = {infinito, -1, -1};
        return vazio;
    }
    noh_heap minimo = heap_minimo[0];
    heap_minimo[0] = heap_minimo[tamanho_heap - 1];
    tamanho_heap--;
    descer_heap(0);
    return minimo;
}


int dijkstra(int n) {
    int i;

    for (i = 1; i <= n; i++) {
        distancias[i][0] = infinito;
        distancias[i][1] = infinito;
    }

    distancias[1][0] = 0;
    inserir_heap(0, 1, 0);

    while (tamanho_heap > 0) {
        noh_heap atual = extrair_minimo();
        int u = atual.cidade;
        int custo_u = atual.custo;
        int paridade_u = atual.paridade;

        if (custo_u > distancias[u][paridade_u]) {
            continue;
        }

        trecho *vizinho = adjacencia[u];
        while (vizinho != NULL) {
            int v = vizinho->destino;
            int peso_uv = vizinho->custo;
            int paridade_v = 1 - paridade_u;

            if (distancias[u][paridade_u] + peso_uv < distancias[v][paridade_v]) {
                distancias[v][paridade_v] = distancias[u][paridade_u] + peso_uv;
                inserir_heap(distancias[v][paridade_v], v, paridade_v);
            }
            vizinho = vizinho->proximo;
        }
    }

    if (distancias[n][0] == infinito) {
        return -1;
    } else {
        return distancias[n][0];
    }
}

void adicionar_trecho(int u, int v, int c) {
    trecho *novo_trecho = (trecho*)malloc(sizeof(trecho));
    novo_trecho->destino = v;
    novo_trecho->custo = c;
    novo_trecho->proximo = adjacencia[u];
    adjacencia[u] = novo_trecho;
}

int main() {
    int n, m, i;
    heap_minimo = (noh_heap*)malloc((max_n * 2 + 1) * sizeof(noh_heap));

    if (scanf("%d %d", &n, &m) != 2) return 0;

    for (i = 1; i <= n; i++) {
        adjacencia[i] = NULL;
    }

    for (i = 0; i < m; i++) {
        int u, v, c;
        if (scanf("%d %d %d", &u, &v, &c) != 3) return 0;

        adicionar_trecho(u, v, c);
        adicionar_trecho(v, u, c);
    }

    int resultado = dijkstra(n);

    printf("%d\n", resultado);
    free(heap_minimo);
    for (i = 1; i <= n; i++) {
        trecho *atual = adjacencia[i];
        while (atual != NULL) {
            trecho *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }

    return 0;
}