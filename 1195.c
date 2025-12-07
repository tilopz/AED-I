#include <stdio.h>
#include <stdlib.h>

typedef struct cel {
    int valor;
    struct cel *esq;
    struct cel *dir;
} no;

typedef no *arvore;

int primeiro_impresso;

arvore insere (arvore r, int x){
    no *novo, *p, *q;

    novo = (no*) malloc(sizeof(no));
    if (novo == NULL) exit(1);
    novo->valor = x;
    novo->esq = novo->dir = NULL;

    if (r == NULL) return novo;

    p = r;
    while (p != NULL){
        q = p;
        if (p->valor > x) p = p->esq;
        else p = p->dir;
    }

    if (q->valor > x) q->esq = novo;
    else q->dir = novo;
    
    return r;
}

void imprime_no(int valor) {
    if (!primeiro_impresso) {
        printf("%d", valor);
        primeiro_impresso = 1;
    } else {
        printf(" %d", valor);
    }
}

void pre_ordem (arvore r){
    if (r != NULL){
        imprime_no(r->valor);
        pre_ordem(r->esq);
        pre_ordem(r->dir);
    }
}

void em_ordem (arvore r){
    if (r != NULL){
        em_ordem(r->esq);
        imprime_no(r->valor);
        em_ordem(r->dir);
    }
}

void pos_ordem (arvore r){
    if (r != NULL){
        pos_ordem(r->esq);
        pos_ordem(r->dir);
        imprime_no(r->valor);
    }
}

void libera (arvore r){
    if (r != NULL){
        libera(r->esq);
        libera(r->dir);
        free(r);
    }
}

int main () {
    int nc, i;
    
    if (scanf ("%d", &nc) != 1) return 1;

    for (i = 1; i <= nc; i++){
        int n, j, x;
        arvore r = NULL;
        
        if (scanf ("%d", &n) != 1) return 1;
        
        for (j = 0; j < n; j++){
            if (scanf ("%d", &x) != 1) {
                libera(r);
                return 1;
            }
            r = insere(r, x);
        }
        
        printf("Case %d:\n", i);

        printf("Pre.: ");
        primeiro_impresso = 0;
        pre_ordem(r);
        printf("\n");

        printf("In..: ");
        primeiro_impresso = 0;
        em_ordem(r);
        printf("\n");

        printf("Post: ");
        primeiro_impresso = 0;
        pos_ordem(r);
        printf("\n\n");

        libera(r);
    }
    return 0;
}