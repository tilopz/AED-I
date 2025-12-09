#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int chave;
    struct No *proximo;
} No;

typedef struct {
    No **tabela;
    int M;
} TabelaHash;

No* criar_no(int chave) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) exit(1);
    novo->chave = chave;
    novo->proximo = NULL;
    return novo;
}

void inicializar_hash(TabelaHash *hash, int M) {
    hash->M = M;
    hash->tabela = (No**) calloc(M, sizeof(No*));
    if (hash->tabela == NULL) exit(1);
}

void inserir_chave(TabelaHash *hash, int chave) {
    int indice = chave % hash->M;
    No *novo_no = criar_no(chave);

    if (hash->tabela[indice] == NULL) {
        hash->tabela[indice] = novo_no;
    } else {
        No *atual = hash->tabela[indice];
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo_no;
    }
}

void liberar_hash(TabelaHash *hash) {
    for (int i = 0; i < hash->M; i++) {
        No *atual = hash->tabela[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(hash->tabela);
}

void imprimir_hash(TabelaHash *hash) {
    for (int i = 0; i < hash->M; i++) {
        printf("%d ->", i);
        No *atual = hash->tabela[i];
        
        while (atual != NULL) {
            printf(" %d ->", atual->chave);
            atual = atual->proximo;
        }
        printf(" \\\n");
    }
}

int main() {
    int N_casos, M, C;

    if (scanf("%d", &N_casos) != 1) return 0;

    for (int i = 0; i < N_casos; i++) {
        if (i > 0) {
            printf("\n");
        }

        if (scanf("%d %d", &M, &C) != 2) break;

        TabelaHash hash;
        inicializar_hash(&hash, M);

        for (int j = 0; j < C; j++) {
            int chave;
            if (scanf("%d", &chave) != 1) break;
            inserir_chave(&hash, chave);
        }

        imprimir_hash(&hash);
        liberar_hash(&hash);
    }

    return 0;
}