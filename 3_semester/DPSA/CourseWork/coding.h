#pragma once

#include "record.h"
#include "vector.h"

class CodeRecordList {
    using code_type = utils::vector<int>;
    using code_list = utils::vector<code_type>;

    struct CodeTable {
        char symbol;
        float probability;
        std::size_t length_code;
        code_type code;
    };

    struct CodeRecord {
        Record rec;

        code_list autor;
        code_list title;
        code_list publish;
    };

    utils::list<Record> _origin_recs;
    utils::list<CodeTable> _alphabet;
    utils::list<CodeRecord> _records;
    float _medium_length;
    float _entropy;

    bool _isExistInAlphabet(char symbol);
    void _addProbability(char symbol);
    void _addInAlphabet(char symbol);
    void _codingAlphabet();
    void _createAlphabet(std::ifstream &file);

    code_list _codingField(char *field, std::size_t size);

    void _printCode(const code_list &code);
    void _printCodeRecord(const CodeRecord &rec);

public:
    CodeRecordList(std::ifstream &file);

    void printCodeAlphabet();
    void codingRecords();
    void printCodeRecords();
    void saveCodeRecords();
};
