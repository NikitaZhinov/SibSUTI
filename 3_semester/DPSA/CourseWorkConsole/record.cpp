#include "record.h"

#include <print>
#include <iostream>
#include <queue>

const std::size_t Record::cout_of_records = 4000;

void Record::__copy__(const Record &other) {
    for (std::size_t i = 0; i < AUTOR_LEN; i++)
        author[i] = other.author[i];
    for (std::size_t i = 0; i < TITLE_LEN; i++)
        title[i] = other.title[i];
    for (std::size_t i = 0; i < PUBLISH_LEN; i++)
        publish[i] = other.publish[i];

    year = other.year;
    count_of_line = other.count_of_line;
}

Record::Record() : year(0), count_of_line(0) {
    author = new char[AUTOR_LEN];
    title = new char[TITLE_LEN];
    publish = new char[PUBLISH_LEN];
}

Record::Record(const Record &other) {
    __copy__(other);
}

Record &Record::operator=(const Record &other) {
    __copy__(other);
    return *this;
}

Record::~Record() {
    delete[] author;
    delete[] title;
    delete[] publish;
}

Record *Record::getRecords(std::ifstream &file_base) {
    Record *records = new Record[cout_of_records];

    for (std::size_t i = 0; i < cout_of_records; i++) {
        Record rec;

        file_base.read(rec.author, rec.AUTOR_LEN);
        file_base.read(rec.title, rec.TITLE_LEN);
        file_base.read(rec.publish, rec.PUBLISH_LEN);
        file_base.read((char *)&rec.year, sizeof(rec.year));
        file_base.read((char *)&rec.count_of_line, sizeof(rec.count_of_line));

        records[i] = rec;
    }

    return records;
}

void Record::printRecord(const Record &rec) {
    std::println("{} | {} | {} | {} | {}", rec.author, rec.title, rec.publish, rec.year, rec.count_of_line);
}

void Record::sortRecords(Record *recs) {
    const int count_of_queue = 256;

    for (int i = 0; i < 3; i++) {
        std::queue<char> Q[count_of_queue];

        for (int j = 0; j < Record::getCountRecords(); j++)
    }
}

std::size_t Record::getCountRecords() {
    return cout_of_records;
}
