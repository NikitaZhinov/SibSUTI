#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    const int N = 5;
    int M;
    scanf("%d", &M);

    int **B = (int **)malloc(sizeof(int *) * M);
    for (int i = 0; i < M; i++)
        B[i] = (int *)malloc(sizeof(int) * N);

    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            B[i][j] = rand() % 100;

    int max_elem = 0;
    int max_i = 0, max_j = 0;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (B[i][j] > max_elem) {
                max_elem = B[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }

    int **C = (int **)malloc(sizeof(int *) * (M - 1));
    for (int i = 0; i < M - 1; i++)
        C[i] = (int *)malloc(sizeof(int) * (N - 1));

    int fi = 0, fj = 0;
    for (int i = 0; i < M; i++) {
        if (i == max_i) {
            fi = 1;
            continue;
        }
        fj = 0;
        for (int j = 0; j < N; j++) {
            if (j == max_j) {
                fj = 1;
                continue;
            }
            C[i - fi][j - fj] = B[i][j];
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            printf("%3d", B[i][j]);
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < M - 1; i++) {
        for (int j = 0; j < N - 1; j++)
            printf("%3d", C[i][j]);
        printf("\n");
    }

    for (int i = 0; i < M; i++)
        free(B[i]);
    free(B);
    for (int i = 0; i < M - 1; i++)
        free(C[i]);
    free(C);

    return 0;
}
