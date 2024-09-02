#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RUN 32

int COMP_SORT = 0;
int COMP_PEREB = 0;
int COMP_BIN = 0;

void insertionSort(int *arr, int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        int f = 1;
        while (j >= left && arr[j] < temp) {
            arr[j + 1] = arr[j];
            j--;
            COMP_SORT++;
            f = 0;
        }
        if (f)
            COMP_SORT++;
        arr[j + 1] = temp;
    }
}

void merge(int *arr, int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    int left[len1], right[len2];
    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < len1 && j < len2) {
        if (left[i] >= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        COMP_SORT++;
        k++;
    }

    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }

    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }
}

int min(int a, int b) { return (a < b) ? a : b; }

void timSort(int *arr, int n) {
    for (int i = 0; i < n; i += RUN)
        insertionSort(arr, i, min((i + RUN - 1), (n - 1)));

    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));

            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
}

int perebor(int *arr, int len, int elem) {
    for (int i = 0; i < len; i++) {
        COMP_PEREB++;
        if (arr[i] == elem)
            return i;
    }
    return -1;
}

int bin_poisk(int *arr, int len, int elem) {
    int left = 0, right = len - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        COMP_BIN++;
        if (arr[mid] == elem)
            return mid;
        else if (arr[mid] > elem) {
            left = mid + 1;
            COMP_BIN++;
        } else
            right = mid - 1;
    }
    return -1;
}

int main() {
    srand(time(NULL));

    int n = 100;
    int a[n];
    for (int i = 0; i < n; i++)
        a[i] = rand() % 100;

    int N = 1000;
    int A[N];
    for (int i = 0; i < N; i++)
        A[i] = rand() % 100;

    timSort(a, n);
    printf("%d\n", COMP_SORT);
    COMP_SORT = 0;
    timSort(A, N);
    printf("%d\n", COMP_SORT);

    perebor(a, n, rand() % 100);
    printf("%d\n", COMP_PEREB);
    COMP_PEREB = 0;
    perebor(A, N, rand() % 100);
    printf("%d\n", COMP_PEREB);

    bin_poisk(a, n, rand() % 100);
    printf("%d\n", COMP_BIN);
    COMP_BIN = 0;
    bin_poisk(A, N, rand() % 100);
    printf("%d\n", COMP_BIN);

    return 0;
}
