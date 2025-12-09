#include <stdio.h>
#include <stdlib.h>

#define MAX_LINHAS 1024
#define MAX_COLUNAS 1024
#define MAX_QUEUE_SIZE (MAX_LINHAS * MAX_COLUNAS)

char grid[MAX_LINHAS][MAX_COLUNAS];
int linhas, colunas;
int dl[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

typedef struct {
    int l; 
    int c; 
} Coordenada;

Coordenada fila[MAX_QUEUE_SIZE];
int front = 0;
int rear = 0;

void enqueue(int l, int c) {
    fila[rear].l = l;
    fila[rear].c = c;
    rear = (rear + 1) % MAX_QUEUE_SIZE;
}

Coordenada dequeue() {
    Coordenada coord = fila[front];
    front = (front + 1) % MAX_QUEUE_SIZE;
    return coord;
}

int is_empty() {
    return front == rear;
}

void pintar_bfs(int l_inicial, int c_inicial) {
    grid[l_inicial][c_inicial] = '*';
    enqueue(l_inicial, c_inicial);
    while (!is_empty()) {
        Coordenada atual = dequeue();
        int l = atual.l;
        int c = atual.c;
        for (int i = 0; i < 4; i++) {
            int nova_l = l + dl[i];
            int nova_c = c + dc[i];
            if (nova_l >= 0 && nova_l < linhas && 
                nova_c >= 0 && nova_c < colunas && 
                grid[nova_l][nova_c] == '.') {
                grid[nova_l][nova_c] = '*';
                enqueue(nova_l, nova_c);
            }
        }
    }
}

int main() {
    if (scanf("%d %d", &linhas, &colunas) != 2) return 0;
    
    for (int i = 0; i < linhas; i++) {
        if (scanf("%s", grid[i]) != 1) return 1;
    }

    int contador_cores = 0;
    
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (grid[i][j] == '.') {
                contador_cores++;
                front = rear = 0; 
                pintar_bfs(i, j);
            }
        }
    }
    
    printf("%d\n", contador_cores);
    
    return 0;
}