#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No *esquerda;
    struct No *direita;
} No;

#define MAX_FILA 500

No* fila[MAX_FILA];
int inicio_fila = 0;
int fim_fila = 0;

void enfileira(No *n) {
    if (fim_fila < MAX_FILA) {
        fila[fim_fila++] = n;
    }
}

No* desenfileira() {
    if (inicio_fila < fim_fila) {
        return fila[inicio_fila++];
    }
    return NULL;
}

int fila_vazia() {
    return inicio_fila == fim_fila;
}

void reinicia_fila() {
    inicio_fila = 0;
    fim_fila = 0;
}

No* novo_no(int valor) {
    No *no = (No*) malloc(sizeof(No));
    if (no == NULL) exit(1);
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

No* insere(No* raiz, int valor) {
    if (raiz == NULL) {
        return novo_no(valor);
    }
    if (valor < raiz->valor) {
        raiz->esquerda = insere(raiz->esquerda, valor);
    } else if (valor > raiz->valor) {
        raiz->direita = insere(raiz->direita, valor);
    }
    return raiz;
}

void travessia_nivel(No* raiz) {
    if (raiz == NULL) return;

    reinicia_fila();
    enfileira(raiz);
    int primeiro = 1;

    while (!fila_vazia()) {
        No *atual = desenfileira();

        if (!primeiro) {
            printf(" ");
        }
        printf("%d", atual->valor);
        primeiro = 0;

        if (atual->esquerda != NULL) {
            enfileira(atual->esquerda);
        }
        if (atual->direita != NULL) {
            enfileira(atual->direita);
        }
    }
}

void libera_arvore(No* no) {
    if (no == NULL) return;
    libera_arvore(no->esquerda);
    libera_arvore(no->direita);
    free(no);
}

int main() {
    int C, n_instancia = 1;
    if (scanf("%d", &C) != 1) return 1;

    while (C--) {
        int N, valor;
        No* raiz = NULL;
        
        if (scanf("%d", &N) != 1) break;

        for (int i = 0; i < N; i++) {
            if (scanf("%d", &valor) != 1) break;
            raiz = insere(raiz, valor);
        }

        printf("Case %d:\n", n_instancia++);

        travessia_nivel(raiz);
        printf("\n");

        libera_arvore(raiz);
        
        printf("\n"); 
    }

    return 0;
}