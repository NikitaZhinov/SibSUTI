#include "String.h"

#include <cmath>

namespace str {
    static bool strcmp(const std::string &str1, const std::string &str2, int &compares, int start = 0) {
        for (int i = 0; i < str2.size(); ++i) {
            ++compares;
            if (str1[i + start] != str2[i]) return false;
        }
        return true;
    }

    std::vector<int> strstr(const std::string &str, const std::string &temp, int &compares) {
        std::vector<int> indexes;

        for (int i = 0; i < str.size() - temp.size(); ++i)
            if (strcmp(str, temp, compares, i)) indexes.push_back(i);

        return indexes;
    }

    static bool is_simple_number(std::size_t n) {
        for (std::size_t i = 2; i < std::sqrt(n); ++i)
            if (n % i == 0) return false;
        return true;
    }

    static std::size_t hash(const std::string &str) {
        std::size_t h = 0;
        std::size_t q = std::pow(2, 61) - 1;
        std::size_t x = 4357;

        for (std::size_t i = 0; i < str.size(); ++i)
            h += (str[i] * static_cast<std::size_t>(std::pow(x, str.size() - i - 1))) % str.size();

        return h;
    }

    std::vector<int> rabin_losos(const std::string &str, const std::string &temp, int &compares) {
        std::vector<int> indexes;

        std::size_t hstr = hash(str);
        std::size_t htemp = hash(temp);

        for (int i = 0; i < str.size() - temp.size(); ++i) {
            if (hstr == htemp && strcmp(str, temp, compares, i)) indexes.push_back(i);
            std::string new_str;
            for (int j = i + 1; j < i + temp.size() + 1; ++j) new_str.push_back(str[j]);
            hstr = hash(new_str);
        }

        return indexes;
    }
} // namespace str
