#include <stdio.h>
#include <stdlib.h>

float pow_na_minimalkah(double x, int n) {
    double res = 1;
    if (n < 0) {
        for (int i = 0; i > n; i--)
            res /= x;
        return res;
    }
    for (int i = 0; i < n; i++)
        res *= x;
    return res;
}

int main() {
    float x;
    int n;
    scanf("%f%d", &x, &n);

    printf("%g\n", pow_na_minimalkah(x, n));

    return 0;
}
