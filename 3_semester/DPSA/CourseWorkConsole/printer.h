#pragma once

#include "record.h"

class Printer {
    static const uint8_t count_line_of_page;
    static const uint8_t max_page;

public:
    static void printRecords(Record *records);
    static void printByPages(Record *records);
};
