#include <stdio.h>
#include <stdlib.h>


typedef struct no_lista {
    int destino;
    struct no_lista *proximo;
} no_lista;

typedef no_lista *lista_adj;

int movimentos;

void adiciona_aresta(lista_adj *lista, int u, int v) {
    no_lista *novo = (no_lista*) malloc(sizeof(no_lista));
    if (novo == NULL) exit(1);
    novo->destino = v;
    novo->proximo = lista[u];
    lista[u] = novo;

    novo = (no_lista*) malloc(sizeof(no_lista));
    if (novo == NULL) exit(1);
    novo->destino = u;
    novo->proximo = lista[v];
    lista[v] = novo;
}

void busca_em_profundidade(int u, lista_adj *lista, int *visitado) {
    visitado[u] = 1;
    
    no_lista *p = lista[u];
    while (p != NULL) {
        int v = p->destino;
        
        if (visitado[v] == 0) {
            movimentos++;
            busca_em_profundidade(v, lista, visitado);
            movimentos++;
        }
        p = p->proximo;
    }
}

void libera_lista_adj(int n, lista_adj *lista) {
    int i;
    for (i = 0; i < n; i++) {
        no_lista *atual = lista[i];
        while (atual != NULL) {
            no_lista *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(lista);
}


int main() {
    int t, i;
    
    if (scanf("%d", &t) != 1) return 1;

    for (i = 0; i < t; i++){
        int inicio, v, a;
        int j, u1, v1;
        
        if (scanf("%d", &inicio) != 1) return 1;

        if (scanf("%d %d", &v, &a) != 2) return 1;
        
        if (v <= 0) {
            printf("0\n");
            continue;
        }

        lista_adj *lista = (lista_adj*) calloc(v, sizeof(lista_adj));
        if (lista == NULL) {
            printf("Erro de alocação!\n");
            return 1;
        }

        int *visitado = (int*) calloc(v, sizeof(int));
        if (visitado == NULL) {
            libera_lista_adj(v, lista);
            printf("Erro de alocação!\n");
            return 1;
        }

        for (j = 0; j < a; j++){
            if (scanf("%d %d", &u1, &v1) != 2) {
                libera_lista_adj(v, lista);
                free(visitado);
                return 1;
            }
            adiciona_aresta(lista, u1, v1);
        }

        movimentos = 0;

        busca_em_profundidade(inicio, lista, visitado);

        printf("%d\n", movimentos);

        libera_lista_adj(v, lista);
        free(visitado);
    }
    
    return 0;
}