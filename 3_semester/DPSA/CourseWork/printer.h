#pragma once

#include "record.h"

class Printer {
    static const uint8_t COUNT_LINE_OF_PAGE;
    static const uint16_t MAX_PAGE;

    static void clearConsole();

public:
    static void printRecords(const list<Record> &records);
    static void printByPages(const list<Record> &records);
    static void printAll(const list<Record> &records);
    static void printSearchRecords(const list<Record> &records);
};
