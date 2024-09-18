#include "record.h"

#include <print>
#include <list>

const uint16_t Record::COUNT_OF_RECORDS = 4000;
const uint8_t Record::AUTOR_LEN = 12;
const uint8_t Record::TITLE_LEN = 32;
const uint8_t Record::PUBLISH_LEN = 16;
const uint8_t Record::BITE_NUMBER = 3;

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

Record::Record(const Record &other) : Record::Record() {
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

list<Record> Record::getRecords(std::ifstream &file_base) {
    list<Record> records(COUNT_OF_RECORDS);

    for (Record &rec : records) {
        file_base.read(rec.author, rec.AUTOR_LEN);
        file_base.read(rec.title, rec.TITLE_LEN);
        file_base.read(rec.publish, rec.PUBLISH_LEN);
        file_base.read((char *)&rec.year, sizeof(rec.year));
        file_base.read((char *)&rec.count_of_line, sizeof(rec.count_of_line));
    }

    return records;
}

void Record::printRecord(const Record &rec) {
    std::println("{} | {} | {} | {} | {}", rec.author, rec.title, rec.publish, rec.year, rec.count_of_line);
}

void Record::sortRecords(list<Record> &recs) {
    const int count_of_queue = 256;

    for (int i = BITE_NUMBER - 1; i >= 0; i--) {
        list<Record> Q[count_of_queue];

        for (auto &rec : recs) {
            int c = 0;
            int j = 0;
            for (int k = 0; k < 2; k++) {
                do {
                    c = rec.title[j++];
                } while (c != ' ');
            }

            int index = std::abs(rec.title[j + i]) % count_of_queue;
            Q[index].push_back(rec);
        }

        recs.clear();
        for (int j = count_of_queue - 1; j >= 0; j--)
            recs.insert(recs.cend(), Q[j]);
    }
}

uint16_t Record::getCountRecords() {
    return COUNT_OF_RECORDS;
}
