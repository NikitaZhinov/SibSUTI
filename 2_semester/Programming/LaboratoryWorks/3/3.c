#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);

    char *is_prime = (char *)malloc((n + 1) * sizeof(char));
    for (int i = 2; i <= n; ++i)
        is_prime[i] = 1;

    for (int i = 2; i * i <= n; ++i)
        if (is_prime[i])
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = 0;

    for (int i = 2; i <= n; ++i)
        if (is_prime[i])
            printf("%d ", i);
    printf("\n");

    free(is_prime);
    return 0;
}