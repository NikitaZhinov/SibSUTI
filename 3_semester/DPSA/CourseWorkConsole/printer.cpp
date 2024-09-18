#include "printer.h"

#include <print>
#include <iostream>
#include <cstdint>

const uint8_t Printer::count_line_of_page = 20;
const uint8_t Printer::max_page = Record::getCountRecords() / Printer::count_line_of_page;

void Printer::printRecords(Record *records) {
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
            break;

        default:
            break;
    }
}

void Printer::printByPages(Record *records) {
    uint8_t mode = 0;
    uint16_t page = 0;

    do {
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
        std::system("cls");
#else
        std::system("clear");
#endif

        for (uint16_t i = count_line_of_page * page; i < count_line_of_page * (page + 1); i++)
            Record::printRecord(records[i]);
        std::println("{}/{}\n", page + 1, max_page);

        std::println("1 - Next page");
        std::println("2 - Previous page");
        std::println("0 - Exit");

        std::cin >> mode;

        switch (mode) {
            case '1':
                if (page < max_page)
                    page++;
                break;

            case '2':
                if (page > 1)
                    page--;
                break;

            default:
                break;
        }

    } while (mode != '0');
}
