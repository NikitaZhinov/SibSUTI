#pragma once

#include "record.h"
#include "vector.h"

class CodeRecordList {
    using code_type = utils::vector<int>;

    struct CodeTable {
        char symbol;
        float probability;
        std::size_t length_code;
        code_type code;
    };

    utils::list<Record> _origin_recs;
    utils::list<CodeTable> _alphabet;
    float _medium_length;
    float _entropy;

    bool _isExistInAlphabet(char symbol);
    void _addProbability(char symbol);
    void _addInAlphabet(char symbol);
    void _codingAlphabet();
    void _createAlphabet(std::ifstream &file);

public:
    CodeRecordList(std::ifstream &file);

    void printCodeAlphabet();
};
