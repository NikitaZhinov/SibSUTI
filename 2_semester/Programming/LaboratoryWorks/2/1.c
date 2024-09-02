#include <stdio.h>

void only_positive_numbers() {
    int num;

    scanf("%d", &num);

    if (num != 0) {
        only_positive_numbers();
        if (num > 0)
            printf("%d\n", num);
    }
}

int main() {
    only_positive_numbers();

    return 0;
}
