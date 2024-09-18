#include "printer.h"

#include <print>
#include <iostream>
#include <cstdint>

const uint8_t Printer::COUNT_LINE_OF_PAGE = 20;
const uint16_t Printer::MAX_PAGE = Record::getCountRecords() / Printer::COUNT_LINE_OF_PAGE;

void Printer::printRecords(const list<Record> &records) {
    std::println("Select the viewing mode:");
    std::println("1 - View by pages");
    std::println("2 - View all");
    std::println("0 - Do not view");

    uint8_t mode = 0;
    std::cin >> mode;

    switch (mode) {
        case '1':
            printByPages(records);
            break;

        case '2':
            printAll(records);
            break;

        default:
            break;
    }
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

        auto start_it = records.begin();
        for (uint16_t i = 0; i < page * COUNT_LINE_OF_PAGE; i++)
            start_it++;
        auto end_it = start_it;
        for (uint16_t i = 0; i < COUNT_LINE_OF_PAGE; i++)
            end_it++;
        for (auto it = start_it; it != end_it; it++)
            Record::printRecord(*it);
        std::println("{}/{}", page + 1, MAX_PAGE);

        std::println("1 - Next page");
        std::println("2 - Previous page");
        std::println("0 - Exit");

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
    for (const Record &rec : records)
        Record::printRecord(rec);
}
