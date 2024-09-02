#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, m = 0, k = 0;
    scanf("%d", &n);
    int *b = (int *)malloc(sizeof(int) * n);
    int *c = NULL;
    int *d = NULL;

    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        b[i] = rand() % 101 - 50;
        if (b[i] > 0) {
            c = realloc(c, (++m) * sizeof(int));
            c[m - 1] = b[i];
        } else if (b[i] < 0) {
            d = realloc(d, (++k) * sizeof(int));
            d[k - 1] = b[i];
        }
    }

    for (int i = 0; i < n; i++)
        printf("%d ", b[i]);
    printf("\n");
    for (int i = 0; i < m; i++)
        printf("%d ", c[i]);
    printf("\n");
    for (int i = 0; i < k; i++)
        printf("%d ", d[i]);
    printf("\n");

    free(b);
    free(c);
    free(d);

    return 0;
}