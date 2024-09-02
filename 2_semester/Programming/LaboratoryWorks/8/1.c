/* Дана информация о школах города. Запись имеет вид: номер школы,
количество выпускников школы, число поступивших в ВУЗ.

1) сформировать массив из записей.
2) отсортировать его с помощью индексного массива по проценту
   поступивших в ВУЗы.
3) вывести данные о количестве выпускников в каждой школе и проценту
   поступивших в ВУЗ. */

#include <stdio.h>

typedef struct {
    int number;
    int vipusknikov;
    int postupivshih;
    float procent_postupivshih;
} School;

int main() {
    const int n = 3;
    School schools[] = {{213, 31, 25, 0}, {345, 24, 3, 0}, {24, 567, 0, 0}};

    // предворительный посчёт процента поступивших
    for (int i = 0; i < n; i++) {
        schools[i].procent_postupivshih = (float)schools[i].postupivshih *
                                          100. / (float)schools[i].vipusknikov;
    }

    // сортировка по проценту поступивших
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (schools[j].procent_postupivshih >
                schools[j + 1].procent_postupivshih) {
                School temp = {schools[j].number, schools[j].vipusknikov,
                               schools[j].postupivshih,
                               schools[j].procent_postupivshih};

                schools[j].number = schools[j + 1].number;
                schools[j].vipusknikov = schools[j + 1].vipusknikov;
                schools[j].postupivshih = schools[j + 1].postupivshih;
                schools[j].procent_postupivshih =
                    schools[j + 1].procent_postupivshih;

                schools[j + 1].number = temp.number;
                schools[j + 1].vipusknikov = temp.vipusknikov;
                schools[j + 1].postupivshih = temp.postupivshih;
                schools[j + 1].procent_postupivshih = temp.procent_postupivshih;
            }
        }
    }

    // вывод данных о количестве выпускников и проценту поступивших каждой школы
    for (int i = 0; i < n; i++)
        printf("%3d %f\n", schools[i].vipusknikov,
               schools[i].procent_postupivshih);

    return 0;
}
