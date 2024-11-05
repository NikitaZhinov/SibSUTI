#pragma once

#include <print>
#include <vector>
#include <algorithm>

template <class T>
struct TreeNode {
    T value;
    TreeNode *left, *right;

    TreeNode(const T &val) : value(val), left(nullptr), right(nullptr) {}
};

template <class T, class TNode = TreeNode<T>>
class GraphicsTree;

template <class T> class ITree {
public:
    virtual void add(const T &) = 0;
    virtual void remove(const T &value) = 0;
    virtual void clear() = 0;
    virtual void printFromUpToDown() = 0;
    virtual void printFromLeftToRight() = 0;
    virtual void printFromDownToUp() = 0;
    virtual std::size_t getSize() = 0;
    virtual std::size_t getHeight() = 0;
    virtual double getMediumHeight() = 0;
    virtual T getSum() = 0;
};

// The binary tree virtual class
template <class T, class TNode = TreeNode<T>>
class BaseTree : public ITree<T> {
    friend GraphicsTree<T, TNode>;

protected:
    TNode *root;

    static void __removeBranch__(TNode *p) {
        if (p != nullptr) {
            __removeBranch__(p->left);
            __removeBranch__(p->right);
            delete p;
        }
    }

    static void __printFromUpToDown__(TNode *p) {
        if (p != nullptr) {
            std::print("{} ", p->value);
            __printFromUpToDown__(p->left);
            __printFromUpToDown__(p->right);
        }
    }

    static void __printFromLeftToRight__(TNode *p) {
        if (p != nullptr) {
            __printFromLeftToRight__(p->left);
            std::print("{} ", p->value);
            __printFromLeftToRight__(p->right);
        }
    }

    static void __printFromDownToUp__(TNode *p) {
        if (p != nullptr) {
            __printFromDownToUp__(p->left);
            __printFromDownToUp__(p->right);
            std::print("{} ", p->value);
        }
    }

    static std::size_t __getSize__(TNode *p) {
        if (p == nullptr)
            return 0;
        return 1 + __getSize__(p->left) + __getSize__(p->right);
    }

    static std::size_t __getHeight__(TNode *p) {
        if (p == nullptr)
            return 0;
        return std::max(__getHeight__(p->left), __getHeight__(p->right)) + 1;
    }

    static std::size_t __getSumLenght__(TNode *p, std::size_t l) {
        if (p == nullptr)
            return 0;
        return l + __getSumLenght__(p->left, l + 1) + __getSumLenght__(p->right, l + 1);
    }

    static T __getSum__(TNode *p) {
        if (p == nullptr)
            return 0;
        return p->value + __getSum__(p->left) + __getSum__(p->right);
    }

    static void __getArrayElementsFromLeftToRight__(TNode *p, std::vector<T> &arr) {
        if (p != nullptr) {
            __getArrayElementsFromLeftToRight__(p->left, arr);
            arr.push_back(p->value);
            __getArrayElementsFromLeftToRight__(p->right, arr);
        }
    }

    static void __getArrayElementsFromUpToDown__(TNode *p, std::vector<T> &arr) {
        if (p != nullptr) {
            arr.push_back(p->value);
            __getArrayElementsFromUpToDown__(p->left, arr);
            __getArrayElementsFromUpToDown__(p->right, arr);
        }
    }

public:
    BaseTree() : root(nullptr) {}

    BaseTree(const BaseTree<T> &other) : BaseTree() {
        std::vector<T> arr;
        __getArrayElementsFromUpToDown__(other.root, arr);
        for (T &elem : arr)
            this->add(elem);
    }

    ~BaseTree() {
        clear();
    }

    void clear() override {
        __removeBranch__(root);
        root = nullptr;
    }

    void printFromUpToDown() override {
        __printFromUpToDown__(root);
        std::println();
    }

    void printFromLeftToRight() override {
        __printFromLeftToRight__(root);
        std::println();
    }

    void printFromDownToUp() override {
        __printFromDownToUp__(root);
        std::println();
    }

    std::size_t getSize() override {
        return __getSize__(root);
    }

    std::size_t getHeight() override {
        return __getHeight__(root);
    }

    double getMediumHeight() override {
        return static_cast<double>(__getSumLenght__(root, 1)) / static_cast<double>(__getSize__(root));
    }

    T getSum() override {
        return __getSum__(root);
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
};

// The random search tree
template <class T, class TNode = TreeNode<T>>
class RSTree : public BaseTree<T, TNode> {
protected:
    TNode *__addRecurs__(const T &val, TNode *cur) {
        if (cur == nullptr)
            return new TNode(val);

        if (val < cur->value)
            cur->left = __addRecurs__(val, cur->left);
        else
            cur->right = __addRecurs__(val, cur->right);
        return cur;
    }

    void __removeRight__(TNode *cur, const T &value) {
        TNode *min_right = cur->right, *min_right_prev = cur;
        while (min_right->left != nullptr) {
            min_right_prev = min_right;
            min_right = min_right->left;
        }
        cur->value = std::move(min_right->value);
        __remove__(min_right, min_right_prev, cur->value);
    }

    void __removeLeft__(TNode *cur, const T &value) {
        TNode *max_left = cur->left, *max_left_prev = cur;
        while (max_left->right != nullptr) {
            max_left_prev = max_left;
            max_left = max_left->right;
        }
        cur->value = std::move(max_left->value);
        __remove__(max_left, max_left_prev, cur->value);
    }

    void __remove__(TNode *cur, TNode *prev, const T &value) {
        if (cur == nullptr)
            return;
        if (this->getSize() == 1) {
            delete this->root;
            this->root = nullptr;
            return;
        }

        if (cur->value == value) {
            if (prev == nullptr) {
                if (cur->left == nullptr && cur->right == nullptr) {
                    delete cur;
                    this->root = nullptr;
                } else if (cur->right != nullptr)
                    __removeRight__(cur, value);
                else
                    __removeLeft__(cur, value);
            } else {
                if (cur->left == nullptr && cur->right == nullptr) {
                    if (cur->value < prev->value) {
                        delete cur;
                        prev->left = nullptr;
                    } else {
                        delete cur;
                        prev->right = nullptr;
                    }
                } else if (cur->right != nullptr)
                    __removeRight__(cur, value);
                else
                    __removeLeft__(cur, value);
            }
        } else {
            if (value < cur->value) __remove__(cur->left, cur, value);
            else __remove__(cur->right, cur, value);
        }
    }

public:
    void add(const T &val) override {
        if (this->root == nullptr)
            this->root = new TNode(val);
        else {
            TNode *cur = this->root, *pred = nullptr;

            do {
                pred = cur;
                if (val < cur->value)
                    cur = cur->left;
                else
                    cur = cur->right;
            } while (cur != nullptr);

            if (val < pred->value)
                pred->left = new TNode(val);
            else
                pred->right = new TNode(val);
        }
    }

    void addRecurs(const T &val) {
        this->root = __addRecurs__(val, this->root);
    }

    void remove(const T &value) override {
        __remove__(this->root, nullptr, value);
    }
};

// The perfectly balanced search tree
template <class T, class TNode = TreeNode<T>>
class PBSTree : public BaseTree<T, TNode> {
    TNode *__newTree__(int64_t left, int64_t right, const std::vector<T> &arr) {
        if (left > right) return nullptr;
        std::size_t medium = (left + right) / 2;
        TNode *p = new TNode(arr[medium]);
        p->left = __newTree__(left, medium - 1, arr);
        p->right = __newTree__(medium + 1, right, arr);
        return p;
    }

public:
    PBSTree() = default;

    PBSTree(std::vector<T> arr) {
        std::sort(arr.begin(), arr.end());
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

    void remove(const T &value) override {}
};
