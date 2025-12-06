#include <stdio.h>
#include <stdlib.h>

int resolver_trilhos(int n, int *ordem_saida){
    int *estacao = (int*) malloc(n * sizeof(int));
    if (estacao == NULL) return 0;

    int topo_estacao = -1;
    int vagao_entrada = 1;
    int indice_saida = 0;
    
    while (indice_saida < n) {
        int vagao_desejado = ordem_saida[indice_saida];

        if (vagao_entrada <= n && vagao_entrada == vagao_desejado) {
            vagao_entrada++;
            indice_saida++;
        }
        else if (topo_estacao != -1 && estacao[topo_estacao] == vagao_desejado) {
            topo_estacao--;
            indice_saida++;
        }
        else if (vagao_entrada <= n) {
            topo_estacao++;
            if (topo_estacao >= n) {
                free(estacao);
                return 0; 
            }
            estacao[topo_estacao] = vagao_entrada;
            vagao_entrada++;
        }
        else {
            free(estacao);
            return 0;
        }
    }

    free(estacao);
    return 1;
}

int main() {
    int n;
    
    while (scanf("%d", &n) == 1 && n != 0) {
        int *ordem_saida;
        int i, j;
        
        while (1) {
            ordem_saida = (int*) malloc(n * sizeof(int));
            if (ordem_saida == NULL) return 1;

            int primeiro_vagao;
            
            if (scanf("%d", &primeiro_vagao) != 1) {
                free(ordem_saida);
                break;
            }
            
            if (primeiro_vagao == 0) {
                free(ordem_saida);
                printf("\n");
                break;
            }
            
            ordem_saida[0] = primeiro_vagao;
            for (j = 1; j < n; j++){
                scanf("%d", &ordem_saida[j]);
            }
            
            if (resolver_trilhos(n, ordem_saida)) {
                printf("Yes\n");
            } else {
                printf("No\n");
            }

            free(ordem_saida);
        }
    }
    return 0;
}