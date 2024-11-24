#pragma once

#include "queue.h"

#include <fstream>

class RecordList;

class CodeRecordList;

class Record {
    friend RecordList;
    friend CodeRecordList;

public:
    static const uint16_t COUNT_OF_RECORDS;
    static const uint8_t AUTOR_LEN;
    static const uint8_t TITLE_LEN;
    static const uint8_t PUBLISH_LEN;
    static const uint8_t BITE_NUMBER;

private:
    char *author;
    char *title;
    char *publish;
    short year;
    short count_of_line;

    void __copy__(const Record &other);

protected:
    static void __getLastName__(char title[], char *last_name, std::size_t size);

public:
    Record();
    Record(const Record &other);
    ~Record();

    Record &operator=(const Record &other);

    static RecordList getRecords(std::ifstream &file_base);
    static void printRecord(const Record &rec);

    friend bool operator<(const Record &a, const Record &b);
    friend bool operator>(const Record &a, const Record &b);
    friend bool operator==(const Record &a, const Record &b);
    friend bool operator<=(const Record &a, const Record &b);
    friend bool operator>=(const Record &a, const Record &b);

    friend bool operator<(const Record &a, const short &b);
    friend bool operator>(const Record &a, const short &b);
    friend bool operator==(const Record &a, const short &b);
};

class RecordList : public Record {
    utils::list<Record> record_list;
    std::unique_ptr<Record *> array_pointers;

    void __init_array__();

public:
    RecordList();
    RecordList(const utils::list<Record> &l);
    RecordList(const RecordList &other);
    RecordList(RecordList &&other) noexcept;

    RecordList &operator=(const utils::list<Record> &l);

    void sort();
    void search(utils::queue<Record> &searched_records, const char *key);

    const utils::list<Record> &getRecordList() const;
    const std::unique_ptr<Record *> &getArrayPointers() const;
};
