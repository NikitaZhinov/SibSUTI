#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int m, n;
    scanf("%d%d", &m, &n);

    int **A = (int **)malloc(sizeof(int *) * m);
    for (int i = 0; i < m; i++)
        A[i] = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            A[i][j] = rand() % 100;

    int **D = (int **)malloc(sizeof(int *) * (m + 1));
    for (int i = 0; i < m + 1; i++)
        D[i] = (int *)malloc(sizeof(int) * (n + 1));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            D[i][j] = A[i][j];

    for (int i = 0; i < m; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++)
            sum += A[i][j];
        D[i][n] = sum;
    }
    for (int j = 0; j < n; j++) {
        int sum = 0;
        for (int i = 0; i < m; i++)
            sum += A[i][j];
        D[m][j] = sum;
    }
    int sum = 0;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            sum += A[i][j];
    D[m][n] = sum;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            printf("%5d", A[i][j]);
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < m + 1; i++) {
        for (int j = 0; j < n + 1; j++)
            printf("%5d", D[i][j]);
        printf("\n");
    }

    for (int i = 0; i < m; i++)
        free(A[i]);
    free(A);
    for (int i = 0; i < m + 1; i++)
        free(D[i]);
    free(D);

    return 0;
}
