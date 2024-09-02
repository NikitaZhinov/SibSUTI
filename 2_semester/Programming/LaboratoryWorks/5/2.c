#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int n = rand() % 10;
    int **table = (int **)malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        table[i] = (int *)malloc(sizeof(int) * (i + 1));
        for (int j = 0; j < i + 1; j++)
            table[i][j] = (i + 1) * (j + 1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i + 1; j++)
            printf("%3d", table[i][j]);
        printf("\n");
    }

    for (int i = 0; i < n; i++)
        free(table[i]);
    free(table);

    return 0;
}