#include "Coding.h"

#include <cmath>
#include <algorithm>

namespace coding {
    void shennon(std::vector<Table> &arr) {
        std::sort(arr.begin(), arr.end(), [](const Table &a, const Table &b) { return a.probability > b.probability; });
        arr.insert(arr.begin(), { 0 });

        auto pred_it = arr.begin();
        for (auto it = ++arr.begin(); it != arr.end(); ++it) {
            it->q = pred_it->q + pred_it->probability;
            it->code.resize(std::ceil(-std::log2(it->probability)));
            ++pred_it;
        }

        for (Table &symbol : arr) {
            for (int &code : symbol.code) {
                symbol.q *= 2;
                code = symbol.q;
                if (symbol.q > 1) --symbol.q;
            }
        }

        arr.erase(arr.begin());
    }

    static int med(std::vector<Table> &arr, int left, int right) {
        float s_left = 0;
        for (int i = left; i < right - 1; ++i) s_left += arr.at(i).probability;
        float s_right = arr.at(right).probability;
        float median = right;
        while (s_left >= s_right) {
            --median;
            s_left -= arr.at(median).probability;
            s_right += arr.at(median).probability;
        }
        return median;
    }

    static void fano(std::vector<Table> &arr, int left, int right, int k) {
        if (left < right) {
            ++k;
            int median = med(arr, left, right);
            for (int i = left; i <= right; ++i) {
                if (i <= median) arr.at(i).code.push_back(0);
                else arr.at(i).code.push_back(1);
            }
            if (median != right) fano(arr, left, median, k);
            fano(arr, median + 1, right, k);
        }
    }

    void fano(std::vector<Table> &arr) {
        std::sort(arr.begin(), arr.end(), [](const Table &a, const Table &b) { return a.probability > b.probability; });
        fano(arr, 0, arr.size() - 1, 0);
        std::sort(arr.begin(), arr.end(), [](const Table &a, const Table &b) { return a.code.size() < b.code.size(); });
    }

    static int up(std::vector<Table> &arr, int n, float q) {
        int j = 0;
        for (int i = n - 2; i > 1; --i) {
            if (arr.at(i - 1).probability <= q) arr.at(i).probability = arr.at(i - 1).probability;
            else j = i;
        }
        arr.at(j).probability = q;
        return j;
    }

    static void down(std::vector<Table> &arr, int n, int j) {
        std::list<int> s = arr.at(j).code;
        for (int i = j; i < n - 2; ++i) arr.at(i).code = arr.at(i + 1).code;

        arr.at(n - 2).code = s;
        arr.at(n - 2).code.push_back(0);
        arr.at(n - 1).code = s;
        arr.at(n - 1).code.push_back(1);
    }

    static void huffman(std::vector<Table> &arr, int n) {
        if (n == 2) {
            arr.front().code.push_back(0);
            arr.at(1).code.push_back(1);
        } else {
            float q = arr.at(n - 2).probability + arr.back().probability;
            int j = up(arr, n, q);
            huffman(arr, n - 1);
            down(arr, n, j);
        }
    }

    void huffman(std::vector<Table> &arr) {
        std::size_t n = arr.size();
        std::sort(arr.begin(), arr.end(), [](const Table &a, const Table &b) { return a.probability > b.probability; });
        huffman(arr, arr.size());
    }
} // namespace coding
