#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
    int val;
    struct celula *prox;
} celula;

typedef struct fila {
    celula *ini;
    celula *fim;
} fila;

void iniciaf (fila *f) {
   f->ini = NULL;
   f->fim = NULL;
}

void push (int x, fila *f) {
    celula *nova;
    nova = malloc(sizeof(celula));
    if (nova == NULL) return;
    
    nova->val = x; 
    nova->prox = NULL; 

    if (f->ini == NULL) { 
        f->ini = nova;
        f->fim = nova;
    } else {
        f->fim->prox = nova; 
        f->fim = nova;
    }
}

int pop (fila *f) {
    if (f->ini == NULL) {
        return -1;
    }
    celula *p;
    int x;
    p = f->ini;
    f->ini = p->prox;
    x = p->val;
    if (f->ini == NULL) {
        f->fim = NULL;
    }
    free (p);
    return x;
}

int ajeitaf (fila *f) {
    int x;
    x = pop(f);
    
    if (f->ini != NULL) { 
        int carta = pop(f);
        push(carta, f);
    }
    
    return x;
}

void liberaf (fila *f) {
    while (f->ini != NULL) {
        pop(f);
    }
}

void resolve () {
    int N;
    
    while(scanf("%d", &N) == 1 && N != 0) {
        
        if (N == 1) {
            printf ("Discarded cards:\nRemaining card: 1\n");
            continue;
        }
        
        fila *f = (fila *)malloc(sizeof(fila));
        if (f == NULL) return; 
        iniciaf(f);
        
        for (int i = 1; i <= N; i++){
            push(i, f);
        }
        
        int descarte[N];
        int descartadas = 0;

        while (f->ini != f->fim) {
            descarte[descartadas++] = ajeitaf(f);
        }
        
        printf("Discarded cards:");
        for (int i = 0; i < descartadas; i++) {
            printf(" %d%s", descarte[i], (i == descartadas - 1) ? "" : ",");
        }
        printf("\n");

        printf("Remaining card: %d\n", pop(f));
        
        liberaf(f);
        free(f);
    }
    
}

int main() {
    resolve();
    
    return 0;
}