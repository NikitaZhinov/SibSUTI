#include "printer.h"

#include <print>
#include <iostream>
#include <cstdint>
#include <Windows.h>

const uint8_t Printer::COUNT_LINE_OF_PAGE = 20;
const uint16_t Printer::MAX_PAGE = Record::COUNT_OF_RECORDS / Printer::COUNT_LINE_OF_PAGE;

void Printer::clearConsole() {
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Printer::printRecords(RecordList &records) {
    uint8_t mode = 0;

    SetConsoleCP(866); // установка кодовой страницы win-cp 866 в поток ввода

    do {
        clearConsole();
        SetConsoleOutputCP(65001); // установка кодовой страницы win-cp 65001 в поток вывода

        std::println("Выберите режим просмотра:");
        std::println("1 - Просмотр по страницам");
        std::println("2 - Посмотреть все");
        std::println("3 - Найти записи");
        std::println("0 - Выход");

        std::cin >> mode;

        switch (mode) {
            case '1':
                printByPages(records);
                break;

            case '2':
                printAll(records);
                break;

            case '3':
                printSearchRecords(records);
                break;

            default:
                break;
        }
    } while (mode != '0');
}

void Printer::printByPages(const RecordList &records) {
    uint8_t mode = 0;
    uint16_t page = 0;

    do {
        clearConsole();
        SetConsoleOutputCP(866);

        auto start_it = records.getRecordList().begin();
        for (uint16_t i = 0; i < page * COUNT_LINE_OF_PAGE; i++)
            start_it++;
        auto end_it = start_it;
        for (uint16_t i = 0; i < COUNT_LINE_OF_PAGE; i++)
            end_it++;
        for (auto it = start_it; it != end_it; it++)
            Record::printRecord(*it);
        std::println("{}/{}\n", page + 1, MAX_PAGE);

        SetConsoleOutputCP(65001);

        std::println("1 - Следующая страница");
        std::println("2 - Предыдущая страница");
        std::println("0 - Назад");

        std::cin >> mode;

        switch (mode) {
            case '1':
                if (page < MAX_PAGE - 1)
                    page++;
                break;

            case '2':
                if (page > 0)
                    page--;
                break;

            default:
                break;
        }

    } while (mode != '0');
}

void Printer::printAll(const RecordList &records) {
    SetConsoleOutputCP(866);
    for (const Record &rec : records.getRecordList())
        Record::printRecord(rec);
    SetConsoleOutputCP(65001);
    char a = 0;
    std::println("\n0 - Назад");
    do {
        std::cin >> a;
    } while (a != '0');
}

void Printer::printSearchRecords(RecordList &records) {
    SetConsoleOutputCP(65001);
    clearConsole();

    std::print("Введите первые {} буквы фамилии замечательного человека: ", Record::BITE_NUMBER);
    std::string key;
    std::cin >> key;
    std::println();

    queue<Record> searched_records;
    records.search(searched_records, key.c_str());

    SetConsoleOutputCP(866);
    while (!searched_records.empty()) {
        Record::printRecord(searched_records.front());
        searched_records.pop();
    }

    SetConsoleOutputCP(65001);
    char a = 0;
    std::println("\n0 - Назад");
    do {
        std::cin >> a;
    } while (a != '0');
}
