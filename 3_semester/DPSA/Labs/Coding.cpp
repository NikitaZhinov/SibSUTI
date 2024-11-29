#include "Coding.h"

#include <cmath>
#include <algorithm>

std::vector<coding::ShennonTable> coding::shennon(std::vector<std::pair<char, float>> p) {
    std::sort(p.begin(), p.end(), [](const std::pair<char, float> &a, const std::pair<char, float> &b) { return a.second > b.second; });
    p.insert(p.begin(), std::pair<char, float>(0, 0.0f));
    std::size_t n = p.size();

    std::vector<float> q(n, 0.0f);
    std::vector<coding::ShennonTable> c(n);
    std::vector<int> l(n);

    for (std::size_t i = 1; i < n; ++i) {
        q.at(i) = q.at(i - 1) + p.at(i - 1).second;
        l.at(i) = std::ceil(-std::log2(p.at(i).second));
    }
    
    for (std::size_t i = 1; i < n; ++i) {
        c.at(i).symbol = p.at(i).first;
        c.at(i).probability = p.at(i).second;
        c.at(i).length_code = l.at(i);
        c.at(i).code = std::vector<int>(l.at(i), 0);
        for (std::size_t j = 0; j < c.at(i).code.size(); ++j) {
            q.at(i) *= 2;
            c.at(i).code.at(j) = q.at(i);
            if (q.at(i) > 1) --q.at(i);
        }
    }

    c.erase(c.begin());
    return c;
}
