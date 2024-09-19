#include "printer.h"

#include <print>
#include <iostream>
#include <cstdint>
#include <Windows.h>

const uint8_t Printer::COUNT_LINE_OF_PAGE = 20;
const uint16_t Printer::MAX_PAGE = Record::getCountRecords() / Printer::COUNT_LINE_OF_PAGE;

void Printer::printRecords(const list<Record> &records) {
    uint8_t mode = 0;

    SetConsoleCP(1251);       // установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

    do {
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
        std::system("cls");
#else
        std::system("clear");
#endif

        std::println("Выберите режим просмотра:");
        std::println("1 - Просмотр по страницам");
        std::println("2 - Посмотреть все");
        std::println("0 - Не просматривать");

        std::cin >> mode;

        switch (mode) {
            case '1':
                printByPages(records);
                mode = '0';
                break;

            case '2':
                printAll(records);
                mode = '0';
                break;

            default:
                break;
        }
    } while (mode != '0');
}

void Printer::printByPages(const list<Record> &records) {
    uint8_t mode = 0;
    uint16_t page = 0;

    do {
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
        std::system("cls");
#else
        std::system("clear");
#endif
        SetConsoleOutputCP(866);

        auto start_it = records.begin();
        for (uint16_t i = 0; i < page * COUNT_LINE_OF_PAGE; i++)
            start_it++;
        auto end_it = start_it;
        for (uint16_t i = 0; i < COUNT_LINE_OF_PAGE; i++)
            end_it++;
        for (auto it = start_it; it != end_it; it++)
            Record::printRecord(*it);
        std::println("{}/{}\n", page + 1, MAX_PAGE);

        SetConsoleOutputCP(1251);

        std::println("1 - Следующая страница");
        std::println("2 - Предыдущая страница");
        std::println("0 - Выход");

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

void Printer::printAll(const list<Record> &records) {
    SetConsoleOutputCP(866);
    for (const Record &rec : records)
        Record::printRecord(rec);
}
