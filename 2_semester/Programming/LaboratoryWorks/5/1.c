#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    int k;
    scanf("%d", &k);

    int m = rand() % 20;
    while (m <= k)
        m = rand() % 20;
    int *A = (int *)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++)
        A[i] = rand() % 100;

    int num_of_str = (m % k == 0) ? (m / k) : (m / k + 1);
    int **B = (int **)malloc(sizeof(int *) * num_of_str);
    int ai = 0;
    for (int i = 0; i < num_of_str; i++) {
        B[i] = (int *)calloc(sizeof(int), k);
        for (int j = 0; j < k; j++)
            B[i][j] = (ai < m) ? A[ai++] : 0;
    }

    for (int i = 0; i < m; i++)
        printf("%d ", A[i]);
    printf("\n");
    for (int i = 0; i < num_of_str; i++) {
        for (int j = 0; j < k; j++)
            printf("%3d", B[i][j]);
        printf("\n");
    }

    for (int i = 0; i < num_of_str; i++)
        free(B[i]);
    free(B);
    free(A);
    return 0;
}
