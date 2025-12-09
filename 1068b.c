#include <stdio.h>
#include <stdlib.h>

typedef struct cel {
    char valor;
    struct cel *prox;
} celula;

typedef celula *pilha_t;

void iniciap(pilha_t *topo_ptr) {
    *topo_ptr = NULL;
}

void push(pilha_t *topo_ptr, char item) {
    celula *novo = (celula *)malloc(sizeof(celula));
    if (novo == NULL) {
        return; 
    }
    novo->valor = item;
    novo->prox = *topo_ptr;
    *topo_ptr = novo;
}

int pop(pilha_t *topo_ptr) {
    if (*topo_ptr == NULL) {
        return 0;
    }
    celula *temp = *topo_ptr;
    *topo_ptr = temp->prox;
    free(temp);
    return 1;
}

int esta_vazia(pilha_t topo) {
    return topo == NULL;
}

int verifica_balanco(char *expressao) {
    pilha_t p;
    iniciap(&p);
    for (int i = 0; expressao[i] != '\0'; i++) {
        char caractere = expressao[i];
        if (caractere == '(') {
            push(&p, caractere);
            
        } else if (caractere == ')') {
            if (!pop(&p)) {
                return 0;
            }
        }
    }
    if (!esta_vazia(p)) {
        return 0;
    }
    return 1;
}

void libera_pilha(pilha_t *topo_ptr) {
    celula *atual = *topo_ptr;
    celula *temp;
    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    *topo_ptr = NULL;
}

int main() {
    char expressao[100001];
    while (scanf("%s", expressao) != EOF) {
        if (verifica_balanco(expressao)) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    }
    return 0;
}