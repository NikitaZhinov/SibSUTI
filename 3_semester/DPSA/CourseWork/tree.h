#pragma once

#include "queue.h"

#include <utility>

template <class T> struct _TreeNode {
    list<T> value;
    _TreeNode *left, *right;

    _TreeNode(const T &val) : value(1, val), left(nullptr), right(nullptr) {}

    _TreeNode(const list<T> &val) : value(val), left(nullptr), right(nullptr) {}
};

template <class T> class tree {
protected:
    struct ElemWithWeight {
        list<T> elem;
        uint64_t weight;
    };

    _TreeNode<T> *root;
    std::size_t size;

    template <class _Iter> uint64_t __calculateWeight__(const T &elem, _Iter left, _Iter right) {
        uint64_t weight = 0;
        for (_Iter it = left; it != right; it++)
            if (elem == *it) weight++;
        return weight;
    }

    uint64_t __sumWeights__(const list<ElemWithWeight> &l) {
        uint64_t sum = 0;
        for (const ElemWithWeight &elem : l)
            sum += elem.weight;
        return sum;
    }

    bool __isExist__(list<ElemWithWeight> &l, const T &val) {
        bool is_exist = false;
        for (ElemWithWeight &elem : l) {
            if (elem.elem.front() == val) {
                is_exist = true;
                elem.elem.push_back(val);
                break;
            }
        }
        return is_exist;
    }

    template <class _Iter> void __create__(_Iter left, _Iter right) {
        uint64_t wes = 0, sum = 0;
        _Iter it = left;
        for (; it != right; it++) wes += it->weight;
        _Iter last = right;
        last--;
        for (it = left; it != right; it++) {
            if (sum < wes / 2 && sum + it->weight > wes / 2) break;
            sum += it->weight;
        }
        it = last;
        __add__(it->elem);
        if (it != left) __create__(left, it);
        if (++it != right) __create__(it, right);
    }

    void __clear__(_TreeNode<T> *p) {
        if (p != nullptr) {
            __clear__(p->left);
            __clear__(p->right);
            delete p;
        }
    }

    void __add__(const list<T> &val) {
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

    template <class P = T> list<T> __find__(_TreeNode<T> *p, const P &key) {
        if (p->value.front() == key) return p->value;
        else if (p->value.front() < key) return __find__(p->right, key);
        return __find__(p->left, key);
    }

    template <class PrintFunc> void __print__(_TreeNode<T> *p, PrintFunc print) {
        if (p != nullptr) {
            __print__(p->left, print);
            for (const T &e : p->value) print(e);
            __print__(p->right, print);
        }
    }

public:
    tree() : root(nullptr) {}

    template <class Contaner> tree(const Contaner &c) {
        list<ElemWithWeight> l;
        auto it = c.begin();
        while (__sumWeights__(l) != c.size()) {
            T val = *it;
            it++;
            if (__isExist__(l, val)) continue;
            l.push_back({ list<T>(1, val), __calculateWeight__(val, c.begin(), c.end()) });
        }
        __create__(l.begin(), l.end());
    }

    ~tree() { clear(); }

    void clear() { __clear__(root); }

    template <class P = T> list<T> find(const P &key) { return __find__(root, key); }

    std::size_t getSize() { return size; }

    template <class PrintFunc> void print(PrintFunc print) { __print__(root, print); }
};
