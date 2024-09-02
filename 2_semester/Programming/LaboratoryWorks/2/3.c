#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void to_binary(int n) {
    if (n > 0) {
        to_binary(n / 2);
        printf("%d", n % 2);
    }
}

int main() {
    srand(time(NULL));
    int num = rand() % 100;
    printf("%d -> ", num);
    to_binary(num);
    printf("\n");

    return 0;
}
