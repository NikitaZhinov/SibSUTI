#pragma once

#include "queue.h"
#include "record.h"

#include <utility>
#include <print>

template <class T> struct _TreeNode {
    utils::list<T> value;
    _TreeNode *left, *right;

    _TreeNode(const T &val) : value(1, val), left(nullptr), right(nullptr) {}

    _TreeNode(const utils::list<T> &val) : value(val), left(nullptr), right(nullptr) {}
};

template <class T> class tree {
protected:
    _TreeNode<T> *root;
    std::size_t size;

    uint64_t __sumWeights__(utils::list<T> *l, const std::size_t &size) {
        uint64_t sum = 0;
        for (std::size_t i = 0; i < size; ++i)
            sum += l[i].size();
        return sum;
    }

    bool __isExist__(utils::list<T> *l, const std::size_t &size, const T &val) {
        for (std::size_t i = 0; i < size; ++i) {
            if (l[i].front() == val) {
                l[i].push_back(val);
                return true;
            }
        }
        return false;
    }

    template <class A> void __create__(const A &arr, int64_t left, int64_t right) {
        if (left <= right) {
            uint64_t wes = 0, sum = 0;
            int64_t i = left;
            for (i = left; i <= right; ++i) wes += arr[i].size();
            for (i = left; i < right; ++i) {
                if (sum < wes / 2 && sum + arr[i].size() >= wes / 2) break;
                sum += arr[i].size();
            }
            __add__(arr[i]);
            __create__(arr, left, i - 1);
            __create__(arr, i + 1, right);
        }
    }

    void __clear__(_TreeNode<T> *p) {
        if (p != nullptr) {
            __clear__(p->left);
            __clear__(p->right);
            delete p;
        }
    }

    void __add__(const utils::list<T> &val) {
        if (root == nullptr)
            root = new _TreeNode(val);
        else {
            _TreeNode<T> *cur = root, *pred = nullptr;

            do {
                pred = cur;
                if (val.front() < cur->value.front())
                    cur = cur->left;
                else
                    cur = cur->right;
            } while (cur != nullptr);

            if (val.front() < pred->value.front())
                pred->left = new _TreeNode(val);
            else
                pred->right = new _TreeNode(val);
        }
        size += val.size();
    }

    template <class P = T> utils::list<T> __find__(_TreeNode<T> *p, const P &key) {
        if (p != nullptr) {
            if (p->value.front() == key) return p->value;
            else if (p->value.front() < key) return __find__(p->right, key);
            return __find__(p->left, key);
        }
        return utils::list<T>();
    }

    template <class PrintFunc> void __print__(_TreeNode<T> *p, PrintFunc print, std::size_t &i) {
        if (p != nullptr) {
            __print__(p->left, print, i);
            for (const T &e : p->value) {
                std::print("{:3} - ", i++);
                print(e);
            }
            __print__(p->right, print, i);
        }
    }

    int64_t __quickSort__(utils::list<T> *&arr, int64_t left, int64_t right) {
        T &pivo = arr[(left + right) / 2].front();
        while (left <= right) {
            while (arr[left].front() < pivo) left++;
            while (arr[right].front() > pivo) right--;
            if (left <= right) std::swap(arr[left++], arr[right--]);
        }
        return left;
    }

    void __sort__(utils::list<T> *&arr, int64_t start, int64_t end) {
        if (start >= end) return;
        int64_t rightStart = __quickSort__(arr, start, end);
        __sort__(arr, start, rightStart - 1);
        __sort__(arr, rightStart, end);
    }

public:
    tree() : root(nullptr) {}

    template <class Contaner> tree(const Contaner &c) {
        utils::list<T> *l = new utils::list<T>[c.size()];
        std::size_t size = 0;
        auto it = c.begin();
        while (__sumWeights__(l, size) != c.size()) {
            T val = *it;
            ++it;
            if (__isExist__(l, size, val)) continue;
            l[size] = utils::list<T>(1, val);
            ++size;
        }
        __sort__(l, 0, size - 1);
        __create__(l, 0, size - 1);
        delete[] l;
    }

    ~tree() { clear(); }

    void clear() { __clear__(root); }

    template <class P = T> utils::list<T> find(const P &key) { return __find__(root, key); }

    std::size_t getSize() { return size; }

    template <class PrintFunc> void print(PrintFunc print) {
        std::size_t i = 1;
        __print__(root, print, i);
    }
};
