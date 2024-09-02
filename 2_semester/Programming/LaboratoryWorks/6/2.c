#include <math.h>
#include <stdio.h>

int fuctorial(int n) {
    if (n < 2)
        return 1;
    return n * fuctorial(n - 1);
}

void some_function(int n, int m, float *pd, float *pm) {
    const float p = 0.45;
    const float q = 1 - p;

    float c =
        (float)fuctorial(n) / ((float)fuctorial(m) * (float)fuctorial(n - m));
    *pd = c * pow(p, m) * pow(q, n - m);
    *pm = c * pow(q, m) * pow(p, n - m);
}

int main() {
    int n, m;
    float pd, pm;
    scanf("%d%d", &n, &m);
    some_function(n, m, &pd, &pm);
    printf("pd = %f; pm = %f\n", pd, pm);

    return 0;
}
