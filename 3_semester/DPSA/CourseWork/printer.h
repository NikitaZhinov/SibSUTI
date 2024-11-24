#pragma once

#include "record.h"

class Printer {
    static const uint8_t COUNT_LINE_OF_PAGE;
    static const uint16_t MAX_PAGE;

    static void clearConsole();

public:
    static void printRecords(RecordList &records, std::ifstream &file_base);
    static void printByPages(const RecordList &records);
    static void printAll(const RecordList &records);
    static void printSearchRecords(RecordList &records);
    static void printSearchTree(utils::list<Record> &records);
    static void printCodeRecords(const RecordList &records, std::ifstream &file_base);
};
