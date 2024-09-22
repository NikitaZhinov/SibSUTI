#pragma once

#include <print>
#include <vector>
#include <algorithm>

template <class T>
class GraphicsTree;

template <class T>
struct BTreeNode {
    T value;
    BTreeNode *left, *right;

    BTreeNode(const T &val) : value(val), left(nullptr), right(nullptr) {}
};

// The binary tree virtual class
template <class T>
class ITree {
    friend GraphicsTree<T>;

protected:
    BTreeNode<T> *root;

    static void __removeBranch__(BTreeNode<T> *p) {
        if (p != nullptr) {
            __removeBranch__(p->left);
            __removeBranch__(p->right);
            delete p;
        }
    }

    static void __printFromUpToDown__(BTreeNode<T> *p) {
        if (p != nullptr) {
            std::print("{} ", p->value);
            __printFromUpToDown__(p->left);
            __printFromUpToDown__(p->right);
        }
    }

    static void __printFromLeftToRight__(BTreeNode<T> *p) {
        if (p != nullptr) {
            __printFromLeftToRight__(p->left);
            std::print("{} ", p->value);
            __printFromLeftToRight__(p->right);
        }
    }

    static void __printFromDownToUp__(BTreeNode<T> *p) {
        if (p != nullptr) {
            __printFromDownToUp__(p->left);
            __printFromDownToUp__(p->right);
            std::print("{} ", p->value);
        }
    }

    static std::size_t __getSize__(BTreeNode<T> *p) {
        if (p == nullptr)
            return 0;
        return 1 + __getSize__(p->left) + __getSize__(p->right);
    }

    static std::size_t __getHeight__(BTreeNode<T> *p) {
        if (p == nullptr)
            return 0;
        return std::max(__getHeight__(p->left), __getHeight__(p->right)) + 1;
    }

    static std::size_t __getSumLenght__(BTreeNode<T> *p, std::size_t l) {
        if (p == nullptr)
            return 0;
        return l + __getSumLenght__(p->left, l + 1) + __getSumLenght__(p->right, l + 1);
    }

    static T __getSum__(BTreeNode<T> *p) {
        if (p == nullptr)
            return 0;
        return p->value + __getSum__(p->left) + __getSum__(p->right);
    }

    void __add__(const T &val) {
        if (this->root == nullptr)
            this->root = new BTreeNode(val);
        else {
            BTreeNode<T> *cur = this->root, *pred = nullptr;

            do {
                pred = cur;
                if (val < cur->value)
                    cur = cur->left;
                else
                    cur = cur->right;
            } while (cur != nullptr);

            if (val < pred->value)
                pred->left = new BTreeNode(val);
            else
                pred->right = new BTreeNode(val);
        }
    }

    static void __getArrayElementsFromLeftToRight__(BTreeNode<T> *p, std::vector<T> &arr) {
        if (p != nullptr) {
            __getArrayElementsFromLeftToRight__(p->left, arr);
            arr.push_back(p->value);
            __getArrayElementsFromLeftToRight__(p->right, arr);
        }
    }

    static void __getArrayElementsFromUpToDown__(BTreeNode<T> *p, std::vector<T> &arr) {
        if (p != nullptr) {
            arr.push_back(p->value);
            __getArrayElementsFromUpToDown__(p->left, arr);
            __getArrayElementsFromUpToDown__(p->right, arr);
        }
    }

public:
    ITree() : root(nullptr) {}

    ITree(const ITree<T> &other) : ITree() {
        std::vector<T> arr;
        __getArrayElementsFromUpToDown__(other.root, arr);
        for (T &elem : arr)
            __add__(elem);
    }

    ~ITree() {
        clear();
    }

    void clear() {
        __removeBranch__(root);
    }

    void printFromUpToDown() {
        __printFromUpToDown__(root);
        std::println();
    }

    void printFromLeftToRight() {
        __printFromLeftToRight__(root);
        std::println();
    }

    void printFromDownToUp() {
        __printFromDownToUp__(root);
        std::println();
    }

    std::size_t getSize() {
        return __getSize__(root);
    }

    std::size_t getHeight() {
        return __getHeight__(root);
    }

    double getMediumHeight() {
        return static_cast<double>(__getSumLenght__(root, 1)) / static_cast<double>(__getSize__(root));
    }

    T getSum() {
        return __getSum__(root);
    }

    void remove(const T &val) {
        if (this->root == nullptr)
            return;

        BTreeNode<T> *cur = this->root, *prev = nullptr;

        while (cur->value != val) {
            prev = cur;

            if (val < cur->value)
                cur = cur->left;
            else
                cur = cur->right;

            if (cur == nullptr)
                return;
        }

        if (prev->left->value == cur->value) {
            prev->left = cur->left;
            if (cur->left == nullptr)
                prev->left = cur->right;
        } else {
            prev->right = cur->left;
            if (cur->left == nullptr)
                prev->right = cur->right;
        }
        delete cur;
    }

    T get(std::size_t index) {
        std::vector<T> arr(getSize());
        __getArrayElementsFromLeftToRight__(root, arr);
        return arr[index];
    }

    std::vector<T> getArrayElementsFromLeftToRight() {
        std::vector<T> arr;
        __getArrayElementsFromLeftToRight__(root, arr);
        return arr;
    }

    std::vector<T> getArrayElementsFromUpToDown() {
        std::vector<T> arr;
        __getArrayElementsFromUpToDown__(root, arr);
        return arr;
    }

    virtual void add(const T &) = 0;
};

// The binary search tree
template <class T>
class BTree : public ITree<T> {
public:
    void add(const T &val) override {
        this->__add__(val);
    }
};

// The perfectly balanced search tree or the random search tree
template <class T>
class PBSTree : public ITree<T> {
private:
    BTreeNode<T> *__newTree__(int64_t left, int64_t right, const std::vector<T> &arr) {
        if (left > right) return nullptr;
        std::size_t medium = (left + right) / 2;
        BTreeNode<T> *p = new BTreeNode<T>(arr[medium]);
        p->left = __newTree__(left, medium - 1, arr);
        p->right = __newTree__(medium + 1, right, arr);
        return p;
    }

public:
    PBSTree() = default;

    PBSTree(const std::vector<T> &arr) {
        this->root = __newTree__(0, arr.size() - 1, arr);
    }

    void add(const T &val) override {
        std::vector<T> arr;
        this->__getArrayElementsFromLeftToRight__(this->root, arr);
        arr.push_back(val);
        std::sort(arr.begin(), arr.end());
        this->clear();
        this->root = __newTree__(0, arr.size() - 1, arr);
    }
};
