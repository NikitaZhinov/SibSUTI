#include <stdio.h>

#define OK 1
#define ERR 0

int perimeter_triangle(float a, float b, float c, float *res) {
    if (a >= b + c || b >= a + c || c >= b + a)
        return ERR;
    *res = a + b + c;
    return OK;
}

int main() {
    float a, b, c, perimeter;
    scanf("%g%g%g", &a, &b, &c);
    if (perimeter_triangle(a, b, c, &perimeter) == OK)
        printf("%g\n", perimeter);
    else
        printf("ERROR!!!\n");

    return 0;
}