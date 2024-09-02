#include "sorts.hpp"

#include <algorithm>
#include <ctime>
#include <functional>
#include <iostream>

template <class T>
double timer_int(std::function<void(std::vector<int, std::allocator<int>> &arr)> sort, T arr) {
    clock_t start = clock();
    sort(arr);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

template <class T>
double timer_double(std::function<void(std::vector<double, std::allocator<double>> &arr)> sort, T arr) {
    clock_t start = clock();
    sort(arr);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    const int n = 10000;

    std::vector<int> arr1(n);
    std::vector<double> arr2(n);
    int i = n;
    for (auto elem : arr1)
        elem = i--;
    i = n;
    for (auto elem : arr1)
        elem = i--;

    std::cout << "BubbleSort: " << timer_int(bubbleSort, arr1)
              << " " << timer_double(bubbleSortd, arr2) << std::endl;
    std::cout << "InsertSort: " << timer_int(insertSort, arr1)
              << " " << timer_double(insertSortd, arr2) << std::endl;
    std::cout << "SelectSort: " << timer_int(selectSort, arr1)
              << " " << timer_double(selectSortd, arr2) << std::endl;

    return 0;
}