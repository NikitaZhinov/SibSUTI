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

void Record::__getLastName__(char title[], char *last_name) {
    int c = 0;
    int j = 0;
    for (int k = 0; k < 2; k++) {
        do {
            c = title[j++];
        } while (c != ' ');
    }
    for (int i = 0; i < BITE_NUMBER; i++)
        last_name[i] = title[j++];
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

uint16_t Record::getCountOfRecords() {
    return COUNT_OF_RECORDS;
}

uint8_t Record::getAutorLen() {
    return AUTOR_LEN;
}

uint8_t Record::getTitleLen() {
    return TITLE_LEN;
}

uint8_t Record::getPublishLen() {
    return PUBLISH_LEN;
}

uint8_t Record::getBiteNumber() {
    return BITE_NUMBER;
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
            char last_name[BITE_NUMBER + 1] = { 0 };
            __getLastName__(rec.title, last_name);

            int index = std::abs(last_name[i]) % count_of_queue;
            Q[index].push_back(rec);
        }

        recs.clear();
        for (int j = count_of_queue - 1; j >= 0; j--)
            recs.insert(recs.cend(), Q[j]);
    }
}

void Record::searchRecords(const list<Record> &records, queue<Record> &searched_records, char *key) {
    for (const Record &record : records) {
        char last_name[BITE_NUMBER + 1] = { 0 };
        __getLastName__(record.title, last_name);

        if (strcmp(last_name, key) == 0)
            searched_records.push(record);
    }
}

uint16_t Record::getCountRecords() {
    return COUNT_OF_RECORDS;
}
