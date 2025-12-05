#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_SIZE 1001

typedef struct {
    int valor[MAX_SIZE];
    int topo;
} pilha;

void iniciapilha(pilha *p) {
    p->topo = -1; 
}
void empilha(pilha *p, int item) {
    p->valor[++p->topo] = item; 
}
int desempilha(pilha *p) {
    return p->valor[p->topo--]; 
}
int pilha_vazia(pilha *p) {
    return p->topo == -1; 
}


typedef struct {
    int valor[MAX_SIZE];
    int inicio, fim;
} fila;

void iniciafila(fila *q) {
    q->inicio = 0; q->fim = -1; 
}
void enfila(fila *q, int item) {
    q->valor[++q->fim] = item; 
}
int desenfila(fila *q) {
    return q->valor[q->inicio++]; 
}
int fila_vazia(fila *q) { 
    return q->inicio > q->fim; 
}


typedef struct {
    int valor[MAX_SIZE];
    int tam;
} filap;

void iniciafilap(filap *fp) {
    fp->tam = 0;
    }
int filap_vazia(filap *fp) {
    return fp->tam == 0;
}


void heapcima(filap *fp, int q) {
    while (q > 0) {
        int p = (q - 1) / 2;
        if (fp->valor[q] > fp->valor[p]) {
            int temp = fp->valor[q];
            fp->valor[q] = fp->valor[p];
            fp->valor[p] = temp;
            q = p;
        } else {
            break;
        }
    }
}

void heapbaixo(filap *fp, int index) {
    int esq, dir, maior;
    while (1) {
        esq = 2 * index + 1;
        dir = 2 * index + 2;
        maior = index;

        if (esq < fp->tam && fp->valor[esq] > fp->valor[maior]) {
            maior = esq;
        }
        if (dir < fp->tam && fp->valor[dir] > fp->valor[maior]) {
            maior = dir;
        }

        if (maior != index) {
            int temp = fp->valor[index];
            fp->valor[index] = fp->valor[maior];
            fp->valor[maior] = temp;
            index = maior;
        } else {
            break;
        }
    }
}

void inserefilap(filap *fp, int item) {
    fp->valor[fp->tam] = item;
    heapcima(fp, fp->tam);
    fp->tam++;
}

int tiramaximofilap(filap *fp) {
    int max = fp->valor[0];
    fp->valor[0] = fp->valor[fp->tam - 1];
    fp->tam--;
    heapbaixo(fp, 0);
    return max;
}


void resolve() {
    int N, op, x;
    int e_pilha, e_fila, e_filap;

    pilha p;
    fila f;
    filap fp;

    while (scanf("%d", &N) == 1) {
        e_pilha = 1;
        e_fila = 1;
        e_filap = 1;

        iniciapilha(&p);
        iniciafila(&f);
        iniciafilap(&fp);

        for (int i = 0; i < N; i++) {
            scanf("%d %d", &op, &x);

            if (op == 1) {
                if (e_pilha) empilha(&p, x);
                if (e_fila) enfila(&f, x);
                if (e_filap) inserefilap(&fp, x);

            } else if (op == 2) {
                int removido_p = -1, removido_f = -1, removido_fp = -1;

                if (e_pilha) {
                    if (pilha_vazia(&p)) {
                        e_pilha = 0;
                    } else {
                        removido_p = desempilha(&p);
                        if (removido_p != x) {
                            e_pilha = 0;
                        }
                    }
                }

                if (e_fila) {
                    if (fila_vazia(&f)) {
                        e_fila = 0;
                    } else {
                        removido_f = desenfila(&f);
                        if (removido_f != x) {
                            e_fila = 0;
                        }
                    }
                }

                if (e_filap) {
                    if (filap_vazia(&fp)) {
                        e_filap = 0;
                    } else {
                        removido_fp = tiramaximofilap(&fp);
                        if (removido_fp != x) {
                            e_filap = 0;
                        }
                    }
                }
            }
        }

        
        int possibilidade = e_pilha + e_fila + e_filap;

        if (possibilidade == 0) {
            printf("impossible\n");
        } else if (possibilidade > 1) {
            printf("not sure\n");
        } else {
            if (e_pilha) {
                printf("stack\n");
            } else if (e_fila) {
                printf("queue\n");
            } else if (e_filap) {
                printf("priority queue\n");
            }
        }
    }
}

int main() {
    resolve();
    return 0;
}