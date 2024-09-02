#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int min(int a, int b) { return (a > b) ? b : a; }

int max(int a, int b) { return (a < b) ? b : a; }

void fffff(int *arr, int n) {
    int min_i = 0, min_i2 = 0;
    int min_elem = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_elem) {
            min_elem = arr[i];
            min_i = i;
        }
    }
    for (int i = 0; i < n; i++)
        if (arr[i] > min_elem)
            min_elem = arr[i];
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_elem) {
            if (i != min_i) {
                min_elem = arr[i];
                min_i2 = i;
            }
        }
    }
    for (int i = 0; i < n; i++)
        if (i > min(min_i, min_i2) && i < max(min_i, min_i2))
            arr[i] = 0;
}

int main() {
    srand(time(NULL));

    const int n = rand() % 20;
    int arr[n];
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 20;

    for (int i = 0; i < n; i++)
        printf("%3d", arr[i]);
    printf("\n");

    fffff(arr, n);

    for (int i = 0; i < n; i++)
        printf("%3d", arr[i]);
    printf("\n");

    return 0;
}