#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000 
char pilha[MAX_SIZE];
int topo;

void iniciap() {
    topo = -1;
}

void push(char item) {
    if (topo < MAX_SIZE - 1) {
        pilha[++topo] = item;
    }
}
    
int pop() {
    if (topo == -1) {
        return 0;
    }
    topo--;
    return 1;
}

int verifica_balanco(char *expressao) {
    iniciap();
    
    for (int i = 0; expressao[i] != '\0'; i++) {
        char caractere = expressao[i];
        
        if (caractere == '(') {
            push(caractere);
            
        } else if (caractere == ')') {
            if (!pop()) {
                
                return 0;
            }
        }
    }

    if (topo != -1) {
        return 0;
    }
    return 1;
}

int main() {
    char expressao[1001];
    while (scanf("%s", expressao) != EOF) {
        
        if (verifica_balanco(expressao)) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    }
    
    return 0;
}