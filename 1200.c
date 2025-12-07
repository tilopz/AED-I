#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cel {
    char valor;
    struct cel *esq;
    struct cel *dir;
} no;

typedef no *arvore;

int primeiro_impresso;

arvore insere (arvore r, char x){
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

int busca (arvore r, char x){
    if (r == NULL) return 0;

    if (r->valor == x) return 1;
    
    if (x < r->valor) {
        return busca(r->esq, x);
    }
    else {
        return busca(r->dir, x);
    }
}

void imprime_no(char valor) {
    if (!primeiro_impresso) {
        printf("%c", valor);
        primeiro_impresso = 1;
    }
    else {
        printf(" %c", valor);
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
    char valor[2]; 
    arvore raiz = NULL;
    
    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        
        if (sscanf(linha, "%s %s", comando, valor) == 2) {
            char x = valor[0];
            
            if (strcmp(comando, "I") == 0) {
                raiz = insere(raiz, x);
            }
            else if (strcmp(comando, "P") == 0) {
                if (busca(raiz, x)) {
                    printf("%c existe\n", x);
                }
                else {
                    printf("%c nao existe\n", x);
                }
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