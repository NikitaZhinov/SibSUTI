#include <stdio.h>
#include <stdlib.h>

char *date_Pascha(int year) {
    static char date[6] = {0};

    int d = (19 * (year % 19) + 15) % 30;
    int f = d + ((2 * (year % 4) + 4 * (year % 7) + 6 * d + 6) % 7);

    if (f <= 26)
        sprintf(date, "%02d.04", f + 4);
    else
        sprintf(date, "%02d.05", f - 26);

    return date;
}

int main() {
    int year;
    scanf("%d", &year);

    printf("%s\n", date_Pascha(year));

    return 0;
}