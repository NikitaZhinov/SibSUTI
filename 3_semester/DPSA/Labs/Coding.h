#pragma once

#include <vector>

namespace coding {
    struct ShennonTable {
        char symbol;
        float probability;
        std::vector<int> code;
        std::size_t length_code;
    };

    std::vector<ShennonTable> shennon(std::vector<std::pair<char, float>> p);
}
