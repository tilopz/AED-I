#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cel {
    int valor;
    struct cel *esq;
    struct cel *dir;
} no;

typedef no *arvore;

int primeiro_impresso;

arvore busca_min (arvore r) {
    if (r == NULL) return NULL;
    if (r->esq == NULL) return r;
    return busca_min(r->esq);
}

arvore busca_max (arvore r) {
    if (r == NULL) return NULL;
    if (r->dir == NULL) return r;
    return busca_max(r->dir);
}


arvore remove_no (arvore r, int x) {
    if (r == NULL) return NULL;
    if (x < r->valor) {
        r->esq = remove_no(r->esq, x);
    } else if (x > r->valor) {
        r->dir = remove_no(r->dir, x);
    } else {
        if (r->esq == NULL) {
            arvore temp = r->dir;
            free(r);
            return temp;
        } else if (r->dir == NULL) {
            arvore temp = r->esq;
            free(r);
            return temp;
        }
        arvore temp = busca_max(r->esq);
        r->valor = temp->valor;
        r->esq = remove_no(r->esq, temp->valor);
    }
    return r;
}

arvore insere (arvore r, int x){
    no *novo, *p, *q;
    
    novo = (no*) malloc(sizeof(no));
    if (novo == NULL) exit(1);
    novo->valor = x;
    novo->esq = novo->dir = NULL;
    
    if (r == NULL) return novo;
    
    p = r;
    q = NULL;
    while (p != NULL){
        q = p;
        if (p->valor > x) p = p->esq;
        else if (p->valor < x) p = p->dir;
        else return r;
    }

    if (q->valor > x) q->esq = novo;
    else q->dir = novo;
    
    return r;
}

int busca (arvore r, int x){
    if (r == NULL) return 0;

    if (r->valor == x) return 1;
    
    if (x < r->valor) {
        return busca(r->esq, x);
    }
    else {
        return busca(r->dir, x);
    }
}

void imprime_no(int valor) {
    if (!primeiro_impresso) {
        printf("%d", valor);
        primeiro_impresso = 1;
    }
    else {
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
    char linha[256];
    char comando[10];
    int valor_int;
    arvore raiz = NULL;
    
    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        if (sscanf(linha, "%s %d", comando, &valor_int) == 2) {
            
            if (strcmp(comando, "I") == 0) {
                raiz = insere(raiz, valor_int);
            }
            else if (strcmp(comando, "P") == 0) {
                if (busca(raiz, valor_int)) {
                    printf("%d existe\n", valor_int);
                }
                else {
                    printf("%d nao existe\n", valor_int);
                }
            }
            else if (strcmp(comando, "R") == 0) {
                raiz = remove_no(raiz, valor_int);
            }
            
        } 
        else if (sscanf(linha, "%s", comando) == 1) {
            
            primeiro_impresso = 0;
            
            if (strcmp(comando, "INFIXA") == 0) {
                em_ordem(raiz);
                printf("\n");
            }
            else if (strcmp(comando, "PREFIXA") == 0) {
                pre_ordem(raiz);
                printf("\n");
            }
            else if (strcmp(comando, "POSFIXA") == 0) {
                pos_ordem(raiz);
                printf("\n");
            }
        }
    }

    libera(raiz);
    
    return 0;
}