#include <iostream>

template <typename T> class Node {
public:
    T val;
    Node *next;
    Node *prev;

    Node(T &_val) :
        val(_val), next(nullptr) {}
};

template <typename T> class List {
public:
    Node<T> *first;
    Node<T> *last;
    size_t len;

    List() :
        first(nullptr), last(nullptr), len(1) {}

    void push_back(T _val) {
        Node<T> *p = new Node<T>(_val);
        if (first == nullptr) {
            first = p;
            last = p;
            return;
        }
        last->prev = last;
        last->next = p;
        last = p;
        len++;
    }

    void remove_first() {
        if (first == nullptr)
            return;
        Node<T> *p = first;
        first = p->next;
        delete p;
    }

    void remove(const size_t index) {
        if (first == nullptr)
            return;
        Node<T> *slow = first;
        Node<T> *fast = first->next;
        size_t i = 0;
        while (fast && i++ + 1 != index) {
            fast = fast->next;
            slow = slow->next;
        }
        if (!fast)
            return;
        slow->next = fast->next;
        delete fast;
        len--;
    }

    Node<T> *operator[](const size_t index) {
        if (first == nullptr)
            return nullptr;
        Node<T> *p = first;
        for (int i = 0; i < index; i++) {
            p = p->next;
            if (!p)
                return nullptr;
        }
        return p;
    }
};

struct Student {
    std::string name;
    int grades[4];
};

int main() {
    List<Student> studentList;
    // clang-format off
    studentList.push_back({"Иван", {4, 4, 4, 5}});
    studentList.push_back({"Тёма", {3, 3, 3, 1}});
    studentList.push_back({"Лёня", {12, 4, 4, 10}});
    // clang-format on

    std::cout << "До:" << std::endl;
    for (size_t i = 0; i < studentList.len; i++) {
        std::cout << "Фамилия: " << studentList[i]->val.name << ", Оценки: ";
        for (int grade : studentList[i]->val.grades)
            std::cout << grade << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (size_t i = 0; i < studentList.len; i++) {
        bool neod = false;
        for (auto grade : studentList[i]->val.grades) {
            if (grade < 3)
                neod = true;
        }
        if (neod)
            studentList.remove(i);
    }

    std::cout << "После:" << std::endl;
    for (size_t i = 0; i < studentList.len; i++) {
        std::cout << "Фамилия: " << studentList[i]->val.name << ", Оценки: ";
        for (int grade : studentList[i]->val.grades)
            std::cout << grade << " ";
        std::cout << std::endl;
    }

    return 0;
}