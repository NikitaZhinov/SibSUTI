#include "sorts.hpp"

void bubbleSort(std::vector<int> &arr) {
    for (int i = 0; i < arr.size() - 1; i++)
        for (int j = 0; j < arr.size() - 1 - i; j++)
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
}

void insertSort(std::vector<int> &arr) {
    for (int i = 1; i < arr.size(); i++) {
        auto t = arr[i];
        long long j = i - 1;
        while (j > -1 and t < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = t;
    }
}

void selectSort(std::vector<int> &arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        int snp = i;
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[j] < arr[snp])
                snp = j;
        std::swap(arr[i], arr[snp]);
    }
}

void bubbleSortd(std::vector<double> &arr) {
    for (int i = 0; i < arr.size() - 1; i++)
        for (int j = 0; j < arr.size() - 1 - i; j++)
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
}

void insertSortd(std::vector<double> &arr) {
    for (int i = 1; i < arr.size(); i++) {
        auto t = arr[i];
        long long j = i - 1;
        while (j > -1 and t < arr[j]) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = t;
    }
}

void selectSortd(std::vector<double> &arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        int snp = i;
        for (int j = i + 1; j < arr.size(); j++)
            if (arr[j] < arr[snp])
                snp = j;
        std::swap(arr[i], arr[snp]);
    }
}
