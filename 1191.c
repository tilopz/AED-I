#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void constroi_e_imprime_pos_ordem(char *pre, char *in, int n) {
    if (n <= 0) {
        return;
    }

    char raiz = pre[0];
    int indice_raiz_in = -1;
    int i;
    for (i = 0; i < n; i++) {
        if (in[i] == raiz) {
            indice_raiz_in = i;
            break;
        }
    }

    if (indice_raiz_in == -1) {
        return; 
    }

    int len_esq = indice_raiz_in;

    int len_dir = n - len_esq - 1;

    constroi_e_imprime_pos_ordem(pre + 1, in, len_esq);

    constroi_e_imprime_pos_ordem(pre + 1 + len_esq, in + len_esq + 1, len_dir);

    printf("%c", raiz);
}

int main() {
    char pre_ordem[53];
    char em_ordem[53];
    int n;

    while (scanf("%s %s", pre_ordem, em_ordem) == 2) {
        
        n = strlen(pre_ordem);
        
        constroi_e_imprime_pos_ordem(pre_ordem, em_ordem, n);
        printf("\n");
    }

    return 0;
}