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
    
void Record::__getLastName__(char title[], char *last_name, std::size_t size) {
    int c = 0;
    int j = 0;
    for (int k = 0; k < 2; k++) {
        do {
            c = title[j++];
        } while (c != ' ');
    }
    for (int i = 0; i < size; i++)
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

Record::~Record() {
    delete[] author;
    delete[] title;
    delete[] publish;
}

RecordList Record::getRecords(std::ifstream &file_base) {
    utils::list<Record> records(COUNT_OF_RECORDS);

    for (Record &rec : records) {
        file_base.read(rec.author, rec.AUTOR_LEN);
        file_base.read(rec.title, rec.TITLE_LEN);
        file_base.read(rec.publish, rec.PUBLISH_LEN);
        file_base.read((char *)&rec.year, sizeof(rec.year));
        file_base.read((char *)&rec.count_of_line, sizeof(rec.count_of_line));
    }

    return RecordList(records);
}

void Record::printRecord(const Record &rec) {
    std::println("{} | {} | {} | {} | {}", rec.author, rec.title, rec.publish, rec.year, rec.count_of_line);
}

bool operator<(const Record &a, const Record &b) {
    return a.year < b.year;
}

bool operator>(const Record &a, const Record &b) {
    return a.year > b.year;
}

bool operator==(const Record &a, const Record &b) {
    return a.year == b.year;
}

bool operator<=(const Record &a, const Record &b) {
    return a < b || a == b;
}

bool operator>=(const Record &a, const Record &b) {
    return a > b || a == b;
}

bool operator<(const Record &a, const short &b) {
    return a.year < b;
}

bool operator>(const Record &a, const short &b) {
    return a.year > b;
}

bool operator==(const Record &a, const short &b) {
    return a.year == b;
}

void RecordList::__init_array__() {
    std::size_t i = 0;
    for (Record &record : record_list)
        array_pointers.get()[i++] = &record;
}

RecordList::RecordList() : record_list(COUNT_OF_RECORDS), array_pointers(new Record *[COUNT_OF_RECORDS]) {
    __init_array__();
}

RecordList::RecordList(const utils::list<Record> &l) : record_list(l), array_pointers(new Record *[COUNT_OF_RECORDS]) {
    __init_array__();
}

RecordList::RecordList(const RecordList &other) : RecordList() {
    record_list = other.record_list;
    __init_array__();
}

RecordList::RecordList(RecordList &&other) noexcept {
    record_list = std::move(other.record_list);
    array_pointers = std::move(other.array_pointers);
}

RecordList &RecordList::operator=(const utils::list<Record> &l) {
    record_list = l;
    __init_array__();
    return *this;
}

void RecordList::sort() {
    const int count_of_queue = 256;

    for (int i = BITE_NUMBER - 1; i >= 0; i--) {
        utils::list<Record> Q[count_of_queue];

        for (auto &rec : record_list) {
            char last_name[BITE_NUMBER + 1] = { 0 };
            __getLastName__(rec.title, last_name, BITE_NUMBER + 1);

            int index = std::abs(last_name[i]) % count_of_queue;
            Q[index].push_back(rec);
        }

        record_list.clear();
        for (int j = count_of_queue - 1; j >= 0; j--)
            record_list.insert(record_list.cend(), Q[j]);
    }

    __init_array__();
}

void RecordList::search(utils::queue<Record> &searched_records, const char *key) {
    std::size_t left = 0, right = COUNT_OF_RECORDS - 1, middle = 0;
    char last_name[BITE_NUMBER + 1] = { 0 };

    while (left < right) {
        middle = (left + right) / 2;
        __getLastName__(array_pointers.get()[middle]->title, last_name, BITE_NUMBER);
        if (strcmp(last_name, key) < 0)
            left = middle + 1;
        else
            right = middle;
    }
    __getLastName__(array_pointers.get()[right]->title, last_name, BITE_NUMBER);
    do {
        searched_records.push(*array_pointers.get()[right++]);
        __getLastName__(array_pointers.get()[right]->title, last_name, BITE_NUMBER);
    } while (strcmp(last_name, key) == 0 && right < COUNT_OF_RECORDS);
}

const utils::list<Record> &RecordList::getRecordList() const {
    return record_list;
}

const std::unique_ptr<Record *> &RecordList::getArrayPointers() const {
    return array_pointers;
}
