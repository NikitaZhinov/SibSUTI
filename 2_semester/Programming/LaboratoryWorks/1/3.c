#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float privedenie(float x) {
    while (fabsf(x) >= 2 * M_PI)
        x -= fabsf(x) / x * 2 * M_PI;
    return x;
}

float cosinus(float x) {
    x = privedenie(x);
    float sum = 1, an = 1, n = 1;

    while (an > 1e-4 || an < -1e-4) {
        an *= -1 * x * x / ((2 * n - 1) * (2 * n));
        sum += an;
        n++;
    }

    return sum;
}

int main() {
    float x;
    scanf("%f", &x);

    printf("%.4f\n", cosinus(x));

    return 0;
}