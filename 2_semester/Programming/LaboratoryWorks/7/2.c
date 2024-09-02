#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sum(int **arr, int lines) {
    for (int i = 0; i < lines; i++) {
        int s = 0;
        for (int j = 0; j < arr[i][0]; j++)
            s += arr[i][j];
        printf("%d ", s);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    const int lines = rand() % 9 + 2;
    int **arr = (int **)malloc(sizeof(int *) * lines);
    for (int i = 0; i < lines; i++) {
        int first = rand() % 10;
        arr[i] = (int *)malloc(sizeof(int) * first);
        arr[i][0] = first;
        for (int j = 1; j < first; j++)
            arr[i][j] = rand() % 10;
    }

    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < arr[i][0]; j++)
            printf("%2d", arr[i][j]);
        printf("\n");
    }
    sum(arr, lines);

    for (int i = 0; i < lines; i++)
        free(arr[i]);
    free(arr);

    return 0;
}
