#pragma once

#include "queue.h"

#include <fstream>

class Record {
    static const uint16_t COUNT_OF_RECORDS;
    static const uint8_t AUTOR_LEN;
    static const uint8_t TITLE_LEN;
    static const uint8_t PUBLISH_LEN;
    static const uint8_t BITE_NUMBER;

    char *author;
    char *title;
    char *publish;
    short year;
    short count_of_line;

    void __copy__(const Record &other);

    static void __getLastName__(char title[], char *last_name);

public:
    Record();
    Record(const Record &other);
    ~Record();

    Record &operator=(const Record &other);

    static uint16_t getCountOfRecords();
    static uint8_t getAutorLen();
    static uint8_t getTitleLen();
    static uint8_t getPublishLen();
    static uint8_t getBiteNumber();

    static list<Record> getRecords(std::ifstream &file_base);
    static void printRecord(const Record &rec);
    static void sortRecords(list<Record> &recs);
    static void searchRecords(const list<Record> &records, queue<Record> &searched_records, char *key);

    static uint16_t getCountRecords();
};
