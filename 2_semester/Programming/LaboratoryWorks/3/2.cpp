#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    int n;
    std::cin >> n;

    double *a = new double[n];
    double **b = new double *[n];

    srand(time(nullptr));
    for (int i = 0; i < n; ++i)
        a[i] = (rand() % 10001) / 100.0;

    for (int i = 0; i < n; ++i)
        b[i] = &a[i];

    std::sort(b, b + n,
              [](const double *x, const double *y) { return *x < *y; });

    for (int i = 0; i < n; ++i)
        std::cout << a[i] << " ";
    std::cout << std::endl;

    for (int i = 0; i < n; ++i)
        std::cout << *b[i] << " ";
    std::cout << std::endl;

    delete[] a;
    delete[] b;

    return 0;
}