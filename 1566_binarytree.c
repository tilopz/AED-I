#include <stdio.h>
#include <stdlib.h>

typedef struct cel {
    int valor;
    struct cel *esq;
    struct cel *dir;
} no;
typedef no *arvore;

arvore Insere (arvore r, int x){
    no *novo, *p, *q;
    novo = malloc(sizeof(no));
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

void Imprime (arvore r){
    if (r != NULL){
        Imprime(r->esq);
        printf ("%d ", r->valor);
        Imprime(r->dir);
    }
}

void Libera (arvore r){
    if (r != NULL){
        Libera(r->esq);
        Libera(r->dir);
        free(r);
    }
}

int main () {
    int NC, i;
    scanf ("%d", &NC);
    if (NC >= 100){
        printf ("Erro na quantidade de casos.\n");
        return 1;
    }

    for (i = 0; i < NC; i++){
        int N, j, x;
        arvore r;

        scanf ("%d", &N);
        if (N <= 1 || N > 3000000){
            printf("Erro no tamanho do vetor.\n");
            return 1;
        }
        
        r = NULL;

        for (j = 0; j < N; j++){
            scanf ("%d", &x);
            if (x < 20 || x > 230){
                printf ("Erro na altura.\n");
                return 1;
            }
            r = Insere(r, x);
        }
        
        Imprime(r);
        printf ("\n");
        Libera(r);

    }
    return 0;
}