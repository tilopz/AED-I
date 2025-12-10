#include <stdio.h>
#include <stdlib.h>

#define MAX_TAREFAS 10000
#define MAX_PRAZO 1000

typedef struct {
    int lucro;
    int prazo;
} Tarefa;

int slots[MAX_PRAZO]; 

int compara_tarefas(const void *a, const void *b) {
    Tarefa *ta = (Tarefa *)a;
    Tarefa *tb = (Tarefa *)b;
    return tb->lucro - ta->lucro;
}

int main() {
    int M;
    int A;

    while (scanf("%d %d", &A, &M) == 2) {
        
        Tarefa tarefas[MAX_TAREFAS];
        int lucro_total_possivel = 0;
        for (int i = 0; i < A; i++) {
            if (scanf("%d %d", &tarefas[i].lucro, &tarefas[i].prazo) != 2) break;
            lucro_total_possivel += tarefas[i].lucro;
        }
        qsort(tarefas, A, sizeof(Tarefa), compara_tarefas);

        for (int i = 0; i < M; i++) {
            slots[i] = -1;
        }

        int lucro_maximo_obtido = 0;
        for (int i = 0; i < A; i++) {
            int lucro_atual = tarefas[i].lucro;
            int prazo_atual = tarefas[i].prazo;
            int limite_busca = (prazo_atual < M) ? prazo_atual : M;

            for (int t = limite_busca - 1; t >= 0; t--) {
                
                if (slots[t] == -1) {
                    slots[t] = i;
                    lucro_maximo_obtido += lucro_atual;
                    break;
                }
            }
        }
        int lucro_perdido = lucro_total_possivel - lucro_maximo_obtido;
        printf("%d\n", lucro_perdido);
    }

    return 0;
}