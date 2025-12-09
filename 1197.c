#include <stdio.h>
#include <stdlib.h>

int main() {
    int v, t, d;

    while (scanf("%d %d", &v, &t) != EOF) {
        d = v * (2 * t);
        printf("%d\n", d);
    }
    
    return 0;
}