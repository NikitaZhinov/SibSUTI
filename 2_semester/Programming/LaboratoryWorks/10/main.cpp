#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

bool cmp(const std::string &left, const std::string &right) {
    return left < right;
}

int main() {
    std::ifstream file1("1.txt");
    std::ofstream file2("2.txt");

    std::vector<std::string> lines;
    std::vector<std::string> words;

    // Код, который от нас трубуют
    while (!file1.eof()) {
        std::string line;
        std::getline(file1, line);
        lines.push_back(line);
    }

    for (auto line : lines) {
        std::string word;
        for (auto symbol : line) {
            if (symbol == ' ') {
                words.push_back(word);
                word = "";
            } else
                word.push_back(symbol);
        }
        if (word.compare("\n") != 0 && word.compare("") != 0)
            words.push_back(word);
    }

    // Нормальный код
    while (!file1.eof()) {
        std::string word;
        file1 >> word;
        words.push_back(word);
    }

    std::sort(words.begin(), words.end(), cmp);

    for (auto word : words)
        file2 << word << '\n';

    file1.close();
    file2.close();

    return 0;
}
