#include <functional>
#include <iostream>

template <typename T> class TreeNode {
public:
    T data;
    size_t key;
    TreeNode *left;
    TreeNode *right;

    TreeNode(const T &value, size_t index) :
        data(value), key(index), left(nullptr), right(nullptr) {}
};

template <typename T> class Tree {
private:
    TreeNode<T> *root;
    size_t _size = 0;

    void insert(const T &value, TreeNode<T> *node, std::function<bool(const T &left, const T &right)> predicade) {
        if (predicade(value, node->data)) {
            if (node->left == nullptr)
                node->left = new TreeNode<T>(value, _size);
            else
                insert(value, node->left, predicade);
        } else {
            if (node->right == nullptr)
                node->right = new TreeNode<T>(value, _size);
            else
                insert(value, node->right, predicade);
        }
    }

    TreeNode<T> *find(const size_t index, TreeNode<T> *node) {
        if (node == nullptr)
            return nullptr;
        if (index == node->key)
            return node;
        if (find(index, node->left) != nullptr)
            return find(index, node->left);
        return find(index, node->right);
    }

public:
    Tree() :
        root(nullptr) {}

    ~Tree() {
        for (size_t i = 0; i < _size; i++)
            delete find(i, root);
    }

    // template <class Predicade>
    void insert(const T &value, std::function<bool(const T &left, const T &right)> predicade) {
        if (root == nullptr)
            root = new TreeNode<T>(value, _size);
        else
            insert(value, root, predicade);
        _size++;
    }

    TreeNode<T> *find(const size_t index) {
        return find(index, root);
    }

    size_t size() {
        return _size;
    }
};

struct Student {
    std::string name;
    int grades[4];
};

bool cmp(const Student &left, const Student &right) {
    return left.name < right.name;
}

int main() {
    Tree<Student> students;
    // clang-format off
    students.insert({"Коля", {67, 7, -2, 4}}, cmp);
    students.insert({"Иван", {4, 4, 4, 5}}, cmp);
    students.insert({"Лёня", {12, 4, 4, 10}}, cmp); // леня жирный уебан
    // clang-format on

    std::cout << "Возврастание:" << std::endl;
    for (size_t i = 0; i < students.size(); i++) {
        Student st = students.find(i)->data;
        std::cout << st.name << " ";
        for (auto grade : st.grades)
            std::cout << grade << " ";
        std::cout << std::endl;
    }

    std::cout << std::endl
              << "Убывание:" << std::endl;
    for (long long i = students.size() - 1; i >= 0; i--) {
        Student st = students.find(i)->data;
        std::cout << st.name << " ";
        for (auto grade : st.grades)
            std::cout << grade << " ";
        std::cout << std::endl;
    }

    return 0;
}