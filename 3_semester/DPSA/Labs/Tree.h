#pragma once

#include <print>
#include <vector>
#include <algorithm>

template <class T>
class GraphicsTree;

template <class T>
struct TreeNode {
    T value;
    TreeNode *left, *right;
    int64_t balance;

    TreeNode(const T &val) : value(val), left(nullptr), right(nullptr), balance(0) {}
};

// The binary tree virtual class
template <class T>
class ITree {
    friend GraphicsTree<T>;

protected:
    TreeNode<T> *root;

    static void __removeBranch__(TreeNode<T> *p) {
        if (p != nullptr) {
            __removeBranch__(p->left);
            __removeBranch__(p->right);
            delete p;
        }
    }

    static void __printFromUpToDown__(TreeNode<T> *p) {
        if (p != nullptr) {
            std::print("{} ", p->value);
            __printFromUpToDown__(p->left);
            __printFromUpToDown__(p->right);
        }
    }

    static void __printFromLeftToRight__(TreeNode<T> *p) {
        if (p != nullptr) {
            __printFromLeftToRight__(p->left);
            std::print("{} ", p->value);
            __printFromLeftToRight__(p->right);
        }
    }

    static void __printFromDownToUp__(TreeNode<T> *p) {
        if (p != nullptr) {
            __printFromDownToUp__(p->left);
            __printFromDownToUp__(p->right);
            std::print("{} ", p->value);
        }
    }

    static std::size_t __getSize__(TreeNode<T> *p) {
        if (p == nullptr)
            return 0;
        return 1 + __getSize__(p->left) + __getSize__(p->right);
    }

    static std::size_t __getHeight__(TreeNode<T> *p) {
        if (p == nullptr)
            return 0;
        return std::max(__getHeight__(p->left), __getHeight__(p->right)) + 1;
    }

    static std::size_t __getSumLenght__(TreeNode<T> *p, std::size_t l) {
        if (p == nullptr)
            return 0;
        return l + __getSumLenght__(p->left, l + 1) + __getSumLenght__(p->right, l + 1);
    }

    static T __getSum__(TreeNode<T> *p) {
        if (p == nullptr)
            return 0;
        return p->value + __getSum__(p->left) + __getSum__(p->right);
    }

    static void __getArrayElementsFromLeftToRight__(TreeNode<T> *p, std::vector<T> &arr) {
        if (p != nullptr) {
            __getArrayElementsFromLeftToRight__(p->left, arr);
            arr.push_back(p->value);
            __getArrayElementsFromLeftToRight__(p->right, arr);
        }
    }

    static void __getArrayElementsFromUpToDown__(TreeNode<T> *p, std::vector<T> &arr) {
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
            add(elem);
    }

    ~ITree() {
        clear();
    }

    void clear() {
        __removeBranch__(root);
        root = nullptr;
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
    virtual void remove(const T &value) = 0;
};

// The binary search tree or the random search tree
template <class T>
class RSTree : public ITree<T> {
    TreeNode<T> *__addRecurs__(const T &val, TreeNode<T> *cur) {
        if (cur == nullptr)
            return new TreeNode<T>(val);

        if (val < cur->value)
            cur->left = __addRecurs__(val, cur->left);
        else
            cur->right = __addRecurs__(val, cur->right);
        return cur;
    }

    void __removeRight__(TreeNode<T> *cur, const T &value) {
        TreeNode<T> *min_right = cur->right, *min_right_prev = cur;
        while (min_right->left != nullptr) {
            min_right_prev = min_right;
            min_right = min_right->left;
        }
        cur->value = std::move(min_right->value);
        __remove__(min_right, min_right_prev, cur->value);
    }

    void __removeLeft__(TreeNode<T> *cur, const T &value) {
        TreeNode<T> *max_left = cur->left, *max_left_prev = cur;
        while (max_left->right != nullptr) {
            max_left_prev = max_left;
            max_left = max_left->right;
        }
        cur->value = std::move(max_left->value);
        __remove__(max_left, max_left_prev, cur->value);
    }

    void __remove__(TreeNode<T> *cur, TreeNode<T> *prev, const T &value) {
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
            this->root = new TreeNode(val);
        else {
            TreeNode<T> *cur = this->root, *pred = nullptr;

            do {
                pred = cur;
                if (val < cur->value)
                    cur = cur->left;
                else
                    cur = cur->right;
            } while (cur != nullptr);

            if (val < pred->value)
                pred->left = new TreeNode(val);
            else
                pred->right = new TreeNode(val);
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
template <class T>
class PBSTree : public ITree<T> {
    TreeNode<T> *__newTree__(int64_t left, int64_t right, const std::vector<T> &arr) {
        if (left > right) return nullptr;
        std::size_t medium = (left + right) / 2;
        TreeNode<T> *p = new TreeNode<T>(arr[medium]);
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

// The AVL tree
template <class T>
class AVLTree : public ITree<T> {
    TreeNode<T> *LLTurn(TreeNode<T> *p) {
        TreeNode<T> *q = p->left;
        p->balance = 0;
        q->balance = 0;
        p->left = q->right;
        q->right = p;
        p = q;
        return p;
    }

    TreeNode<T> *RRTurn(TreeNode<T> *p) {
        TreeNode<T> *q = p->right;
        p->balance = 0;
        q->balance = 0;
        p->right = q->left;
        q->left = p;
        p = q;
        return p;
    }

    TreeNode<T> *LRTurn(TreeNode<T> *p) {
        TreeNode<T> *q = p->left;
        TreeNode<T> *r = q->right;

        if (r->balance < 0) p->balance = 1;
        else p->balance = 0;

        if (r->balance > 0) q->balance = -1;
        else q->balance = 0;

        r->balance = 0;
        q->right = r->left;
        p->left = r->right;
        r->left = q;
        r->right = p;
        p = r;
        return p;
    }

    TreeNode<T> *RLTurn(TreeNode<T> *p) {
        TreeNode<T> *q = p->right;
        TreeNode<T> *r = q->left;

        if (r->balance > 0) p->balance = -1;
        else p->balance = 0;

        if (r->balance < 0) q->balance = 1;
        else q->balance = 0;

        r->balance = 0;
        q->left = r->right;
        p->right = r->left;
        r->right = q;
        r->left = p;
        p = r;
        return p;
    }

    TreeNode<T> *__add__(const T &val, TreeNode<T> *p, bool &rost) {
        if (p == nullptr) {
            p = new TreeNode(val);
            rost = true;
        } else if (p->value > val) {
            p->left = __add__(val, p->left, rost);
            if (rost) {
                if (p->balance > 0) {
                    p->balance = 0;
                    rost = false;
                } else if (p->balance == 0) {
                    p->balance = -1;
                    rost = true;
                } else {
                    if (p->left->balance < 0) p = LLTurn(p);
                    else p = LRTurn(p);
                    rost = false;
                }
            }
        } else {
            p->right = __add__(val, p->right, rost);
            if (rost) {
                if (p->balance < 0) {
                    p->balance = 0;
                    rost = false;
                } else if (p->balance == 0) {
                    p->balance = 1;
                    rost = true;
                } else {
                    if (p->right->balance > 0) p = RRTurn(p);
                    else p = RLTurn(p);
                    rost = false;
                }
            }
        }
        return p;
    }

public:
    void add(const T &val) override {
        bool rost = true;
        this->root = __add__(val, this->root, rost);
    }

    void remove(const T &val) override {}
};
