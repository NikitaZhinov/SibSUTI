#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_negatives(int arr[], int n, int i) {
    if (i == n)
        return;

    if (arr[i] < 0)
        printf("%d\n", arr[i]);
    print_negatives(arr, n, i + 1);
}

void print_positives(int arr[], int n, int i) {
    if (i == n)
        return;

    if (arr[i] > 0)
        printf("%d\n", arr[i]);
    print_positives(arr, n, i + 1);
}

int main() {
    srand(time(NULL));
    int n = rand() % 20;
    int arr[n];
    for (int i = 0; i < n; i++) {
        int num = rand() % 100 - 50;
        while (num == 0)
            num = rand() % 100 - 50;
        arr[i] = num;
    }
    printf("Все числа\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    printf("Отрицательные числа:\n");
    print_negatives(arr, n, 0);

    printf("Положительные числа:\n");
    print_positives(arr, n, 0);

    return 0;
}
