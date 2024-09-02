#include <iostream>

template <typename T> class Node {
public:
    T val;
    Node *next;

    Node(T &_val) :
        val(_val), next(nullptr) {}
};

template <typename T> class ForwardList {
public:
    Node<T> *first;
    Node<T> *last;
    size_t len;

    ForwardList() :
        first(nullptr), last(nullptr), len(1) {}

    void push_back(T _val) {
        Node<T> *p = new Node<T>(_val);
        if (first == nullptr) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
        len++;
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
    ForwardList<Student> studentList;
    // clang-format off
    studentList.push_back({"Иван", {4, 4, 4, 5}});
    studentList.push_back({"Тёма", {3, 3, 3, 1}});
    studentList.push_back({"Лёня", {12, 4, 4, 10}});
    // clang-format on

    for (size_t i = 0; i < studentList.len; i++) {
        for (size_t j = 0; j < studentList.len - i - 1; j++) {
            if (studentList[j]->val.name > studentList[j + 1]->val.name) {
                Student temp = studentList[j]->val;
                studentList[j]->val = studentList[j + 1]->val;
                studentList[j + 1]->val = temp;
            }
        }
    }

    for (size_t i = 0; i < studentList.len; i++) {
        std::cout << "Фамилия: " << studentList[i]->val.name << ", Оценки: ";
        for (int grade : studentList[i]->val.grades)
            std::cout << grade << " ";
        std::cout << std::endl;
    }

    return 0;
}