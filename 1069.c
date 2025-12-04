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

int acha_diamantes(char *areia) {
    iniciap();
    int achados = 0;
    
    for (int i = 0; areia[i] != '\0'; i++) {
        char diamante = areia[i];
        
        if (diamante == '<') {
            push(diamante);
            
        } else if (diamante == '>') {
            if (pop()){
                achados++;
            }
        }
    }
    return achados;
}

int main() {
    char areia[1001];
    int N;
    scanf ("%d", &N);
    
    for (int i = 0; i < N; i++){
        scanf ("%s", &areia);
        printf ("%d\n", acha_diamantes(areia));
    }
    
    return 0;
}