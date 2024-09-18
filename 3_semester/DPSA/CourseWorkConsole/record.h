#pragma once

#include <fstream>

class Record {
    static const std::size_t cout_of_records;

    const std::size_t AUTOR_LEN = 12;
    char *author;

    const std::size_t TITLE_LEN = 32;
    char *title;

    const std::size_t PUBLISH_LEN = 16;
    char *publish;

    short year;
    short count_of_line;

    void __copy__(const Record &other);

public:
    Record();
    Record(const Record &other);
    ~Record();

    Record &operator=(const Record &other);

    static Record *getRecords(std::ifstream &file_base);
    static void printRecord(const Record &rec);
    static void sortRecords(Record *recs);
   
    static std::size_t getCountRecords();
};
