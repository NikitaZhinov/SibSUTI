#pragma once

#include "Tree.h"

#include <utility>
#include <list>

template <class T> struct OSTree {
    T value;
    OSTree *left, *right;
    uint64_t weight;

    OSTree(const T &val) : value(val), left(nullptr), right(nullptr), weight(0) {}

    OSTree(const T &val, const uint64_t &w) : value(val), left(nullptr), right(nullptr), weight(w) {}
};

// The exact optimal search tree
template <class T> class EOSTree : public RSTree<T, OSTree<T>> {
    using WeightsMatrix_t = std::vector<std::vector<uint64_t>>;

protected:
    WeightsMatrix_t AW;
    WeightsMatrix_t AP;
    WeightsMatrix_t AR;

    void __calculateAW__(const std::vector<std::pair<T, uint64_t>> &arr) {
        for (std::size_t i = 0; i < AW.size(); i++)
            for (std::size_t j = i + 1; j < AW.size(); j++)
                AW.at(i).at(j) = AW.at(i).at(j - 1) + arr.at(j).second;
    }

    void __calculateAPAndAR__() {
        for (int i = 0; i < AW.size() - 1; i++) {
            int j = i + 1;
            AP.at(i).at(j) = AW.at(i).at(j);
            AR.at(i).at(j) = j;
        }
        for (int h = 2; h < AW.size(); h++) {
            for (int i = 0; i < AW.size() - h; i++) {
                int j = i + h;
                int m = AR.at(i).at(j - 1);
                int min = AP.at(i).at(m - 1) + AP.at(m).at(j);
                for (int k = m + 1; k <= AR.at(i + 1).at(j); k++) {
                    int x = AP.at(i).at(k - 1) + AP.at(k).at(j);
                    if (x < min) {
                        m = k;
                        min = x;
                    }
                }
                AP.at(i).at(j) = min + AW.at(i).at(j);
                AR.at(i).at(j) = m;
            }
        }
    }

    void __create__(const std::vector<std::pair<T, uint64_t>> &arr, std::size_t left, std::size_t right) {
        if (left < right) {
            std::size_t k = AR.at(left).at(right);
            __add__(arr.at(k));
            __create__(arr, left, k - 1);
            __create__(arr, k, right);
        }
    }

    void __printA__(const WeightsMatrix_t &A) {
        for (const auto &vec : A) {
            for (const auto &weight : vec)
                std::print("{} ", weight);
            std::println();
        }
    }

    int __sumLengthWaysTreeDOP__(OSTree<T> *p, int L) {
        if (p == nullptr) return 0;
        return p->weight * L + __sumLengthWaysTreeDOP__(p->left, L + 1) + __sumLengthWaysTreeDOP__(p->right, L + 1);
    }

    int __weightTree__(OSTree<T> *p) {
        if (p == nullptr) return 0;
        return p->weight + __weightTree__(p->left) + __weightTree__(p->right);
    }

    void __add__(const std::pair<T, uint64_t> &val) {
        if (this->root == nullptr)
            this->root = new OSTree(val.first, val.second);
        else {
            OSTree<T> *cur = this->root, *pred = nullptr;

            do {
                pred = cur;
                if (val.first < cur->value)
                    cur = cur->left;
                else
                    cur = cur->right;
            } while (cur != nullptr);

            if (val.first < pred->value)
                pred->left = new OSTree(val.first, val.second);
            else
                pred->right = new OSTree(val.first, val.second);
        }
    }

public:
    EOSTree(std::vector<std::pair<T, uint64_t>> arr) : AW(arr.size() + 1, std::vector<uint64_t>(arr.size() + 1, 0)),
                                                       AP(arr.size() + 1, std::vector<uint64_t>(arr.size() + 1, 0)),
                                                       AR(arr.size() + 1, std::vector<uint64_t>(arr.size() + 1, 0)) {
        arr.push_back(std::pair<T, uint64_t>());
        __calculateAW__(arr);
        __calculateAPAndAR__();
        __create__(arr, 0, arr.size() - 1);
    }

    void printAW() { __printA__(AW); }

    void printAP() { __printA__(AP); }

    void printAR() { __printA__(AR); }

    const WeightsMatrix_t &getAW() { return AW; }

    const WeightsMatrix_t &getAP() { return AP; }

    const WeightsMatrix_t &getAR() { return AR; }

    double weightedAverageHeightTree() { return static_cast<double>(__sumLengthWaysTreeDOP__(this->root, 1)) / static_cast<double>(__weightTree__(this->root)); }
};

template <class T> class OSTreeA1 : public RSTree<T, OSTree<T>> {
public:
    OSTreeA1(std::vector<std::pair<T, uint64_t>> arr) {
        std::sort(arr.begin(), arr.end(), [](const std::pair<T, uint64_t> &a, const std::pair<T, uint64_t> &b) { return a.second < b.second; });
        for (const std::pair<T, uint64_t> &elem : arr) this->add(elem.first);
    }
};

template <class T> class OSTreeA2 : public RSTree<T, OSTree<T>> {
protected:
    void __create__(const std::vector<std::pair<T, uint64_t>> &arr, int64_t left, int64_t right) {
        std::size_t wes = 0, sum = 0;
        if (left <= right) {
            std::size_t i = left;
            for (i = left; i < right; i++) wes += arr.at(i).second;
            for (i = left; i < right; i++) {
                if (sum < wes / 2 && sum + arr.at(i).second > wes / 2) break;
                sum += arr.at(i).second;
            }
            __add__(arr.at(i));
            __create__(arr, left, i - 1);
            __create__(arr, i + 1, right);
        }
    }

    void __add__(const std::pair<T, uint64_t> &val) {
        if (this->root == nullptr)
            this->root = new OSTree(val.first, val.second);
        else {
            OSTree<T> *cur = this->root, *pred = nullptr;

            do {
                pred = cur;
                if (val.first < cur->value)
                    cur = cur->left;
                else
                    cur = cur->right;
            } while (cur != nullptr);

            if (val.first < pred->value)
                pred->left = new OSTree(val.first, val.second);
            else
                pred->right = new OSTree(val.first, val.second);
        }
    }

public:
    OSTreeA2(const std::vector<std::pair<T, uint64_t>> &arr) { __create__(arr, 0, arr.size() - 1); }
};
