#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int number;
    float square;
    const char *fakultet;
    int viligers;
} Room;

int main() {
    const int n = 4;
    Room rooms[] = {{1, 5.5, "tehnic", 3},
                    {2, 3.5, "tehnic", 2},
                    {3, 7.5, "pochta", 1},
                    {4, 0.5, "urist", 11}};

    char **fakultets = (char **)malloc(sizeof(char *));
    int m = 0;

    for (int i = 0; i < n; i++) {
        int f = 0;
        for (int j = 0; j < m; j++) {
            if (strcmp(fakultets[j], rooms[i].fakultet) == 0)
                f = 1;
        }
        if (!f) {
            fakultets = (char **)realloc(fakultets, sizeof(char *) * (++m));
            fakultets[m - 1] =
                (char *)malloc(sizeof(char) * strlen(rooms[i].fakultet));
            strcpy(fakultets[m - 1], rooms[i].fakultet);
        }
    }

    for (int i = 0; i < m; i++) {
        int rms = 0;
        int students = 0;
        float s = 0;
        for (int j = 0; j < n; j++) {
            if (strcmp(fakultets[i], rooms[j].fakultet) == 0) {
                rms++;
                students += rooms[j].viligers;
                s += rooms[j].square;
            }
        }
        printf("%s:\n\trooms - %d\n\tstudents - %d\n\taverage area - %g\n",
               fakultets[i], rms, students, s / (float)students);
    }

    free(fakultets);

    return 0;
}
