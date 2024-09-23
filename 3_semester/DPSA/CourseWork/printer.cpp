#include "printer.h"

#include <print>
#include <iostream>
#include <cstdint>
#include <Windows.h>

const uint8_t Printer::COUNT_LINE_OF_PAGE = 20;
const uint16_t Printer::MAX_PAGE = Record::getCountRecords() / Printer::COUNT_LINE_OF_PAGE;

void Printer::clearConsole() {
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Printer::printRecords(const list<Record> &records) {
    uint8_t mode = 0;

    SetConsoleCP(866); // ��������� ������� �������� win-cp 1251 � ����� �����

    do {
        clearConsole();
        SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������

        std::println("�������� ����� ���������:");
        std::println("1 - �������� �� ���������");
        std::println("2 - ���������� ���");
        std::println("3 - ����� ������");
        std::println("0 - �����");

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

void Printer::printByPages(const list<Record> &records) {
    uint8_t mode = 0;
    uint16_t page = 0;

    do {
        clearConsole();
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

        std::println("1 - ��������� ��������");
        std::println("2 - ���������� ��������");
        std::println("0 - �����");

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
    SetConsoleOutputCP(1251);
    char a = 0;
    std::println("\n0 - �����");
    do {
        std::cin >> a;
    } while (a != '0');
}

void Printer::printSearchRecords(const list<Record> &records) {
    SetConsoleOutputCP(1251);
    clearConsole();

    std::print("������� ������ {} ����� ������� �������������� ��������: ", Record::getBiteNumber());
    std::string key_string;
    std::cin >> key_string;
    std::println();

    std::unique_ptr<char> key = std::unique_ptr<char>(new char[Record::getBiteNumber() + 1]);
    for (int i = 0; i < Record::getBiteNumber() + 1; i++)
        key.get()[i] = key_string[i];

    queue<Record> searched_records;
    Record::searchRecords(records, searched_records, key.get());

    SetConsoleOutputCP(866);
    while (!searched_records.empty()) {
        Record::printRecord(searched_records.front());
        searched_records.pop();
    }

    SetConsoleOutputCP(1251);
    char a = 0;
    std::println("\n0 - �����");
    do {
        std::cin >> a;
    } while (a != '0');
}
