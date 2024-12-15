#include "coding.h"

#include <fstream>
#include <print>

bool CodeRecordList::_isExistInAlphabet(char symbol) {
    for (const CodeTable &code : _alphabet)
        if (code.symbol == symbol)
            return true;
    return false;
}

void CodeRecordList::_addProbability(char symbol) {
    for (CodeTable &code : _alphabet)
        if (code.symbol == symbol)
            ++code.probability;
}

void CodeRecordList::_addInAlphabet(char symbol) {
    if (!_isExistInAlphabet(symbol)) _alphabet.push_back({ symbol, 0.0f, 0, {} });
    else _addProbability(symbol);
}

void CodeRecordList::_codingAlphabet() {
    _alphabet.sort([](const CodeTable &a, const CodeTable &b) { return a.symbol < b.symbol; });

    utils::vector<float> q(_alphabet.size(), 0.0f);

    float pr = 0.0f;
    auto it = _alphabet.begin();
    for (std::size_t i = 0; i < _alphabet.size(); ++i) {
        q.at(i) = pr + it->probability / 2.0f;
        pr += it->probability;
        it->length_code = -std::log2(it->probability) + 1;
        _medium_length += it->probability * it->length_code;
        _entropy += it->probability * -std::log2(it->probability);
        ++it;
    }

    it = _alphabet.begin();
    for (std::size_t i = 0; i < _alphabet.size(); ++i) {
        it->code = utils::vector<int>(it->length_code, 0);
        for (std::size_t j = 0; j < it->length_code; ++j) {
            q.at(i) *= 2.0f;
            it->code.at(j) = q.at(i);
            if (q.at(i) > 1.0f) --q.at(i);
        }
        ++it;
    }
}

void CodeRecordList::_createAlphabet(std::ifstream &file) {
    std::size_t chars_number = 0;
    file.seekg(0);
    while (!file.eof()) {
        char c;
        file.read(&c, 1);
        _addInAlphabet(c);
        ++chars_number;
    }
    for (CodeTable &code : _alphabet) ++code.probability /= static_cast<float>(chars_number);
}

CodeRecordList::CodeRecordList(std::ifstream &file) : _medium_length(0), _entropy(0) {
    _createAlphabet(file);
    _codingAlphabet();
}

void CodeRecordList::printCodeAlphabet() {
    std::println(" Char | Probability | Length Code | Code");
    for (const CodeTable &line : _alphabet) {
        std::print("{:5} | {:11f} | {:11} | ", line.symbol, line.probability, line.length_code);
        for (std::size_t i = 0; i < line.code.size(); ++i) std::print("{}", line.code.at(i));
        std::println();
    }

    std::println("\nSize: {}\n", _alphabet.size());

    std::println("\nMedium Length = {}", _medium_length);
    std::println("Entropy = {}", _entropy);
    std::println("Medium Length - Entropy = {}", _medium_length - _entropy);
}
