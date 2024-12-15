#include <print>
#include <iostream>
#include <Windows.h>
#include <fstream>

namespace utils {
    template <class T> class vector {
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using self = vector<value_type>;
        using reference_self = self &;
        using const_reference_self = const self &;
        using pointer_self = self *;
        using const_pointer_self = const self *;
        using rvalue_self = self &&;
        using size_type = std::size_t;
        pointer _values;
        size_type _size;

        void _copy(const_reference_self other) {
            clear();
            _size = other._size;
            _values = new value_type[_size];
            for (size_type i = 0; i < _size; ++i) _values[i] = other._values[i];
        }

        void _move(rvalue_self other) {
            clear();
            _size = other._size;
            other._size = 0;
            _values = other._values;
            other._values = nullptr;
        }

    public:
        vector() : _values(nullptr), _size(0) {}

        vector(size_type count) : _values(new value_type[count]), _size(count) {}

        vector(size_type count, const_reference value) : vector(count) {
            for (size_type i = 0; i < count; ++i) _values[i] = value;
        }

        vector(const_reference_self other) : vector() { _copy(other); }

        vector(rvalue_self other) noexcept : vector() { _move(std::move(other)); }

        ~vector() { clear(); }

        reference_self operator=(const_reference_self right) {
            _copy(right);
            return *this;
        }

        reference_self operator=(rvalue_self right) noexcept {
            _move(std::move(right));
            return *this;
        }

        void clear() {
            if (_values != nullptr) delete[] _values;
            _values = nullptr;
            _size = 0;
        }

        reference operator[](size_type index) { return _values[index]; }

        const_reference operator[](size_type index) const { return _values[index]; }

        reference at(size_type index) {
            if (index >= _size) throw std::out_of_range("going beyond the allowed range");
            return _values[index];
        }

        const_reference at(size_type index) const {
            if (index >= _size) throw std::out_of_range("going beyond the allowed range");
            return _values[index];
        }

        size_type size() const noexcept { return _size; }
    };

    template <class Type> struct _List_node {
        _List_node *next_, *prev_;
        Type value_;

        _List_node(const Type &value) : next_(nullptr), prev_(nullptr), value_(value) {}
    };

    template <class Type> struct _List_iterator {
        typedef _List_iterator<Type> _self;
        typedef _List_node<Type> _node;
        typedef Type *pointer;
        typedef Type &reference;

        _node *current;
        _node *last;

        _List_iterator() noexcept : current(nullptr), last(nullptr) {}

        _List_iterator(_node *pointer) noexcept : current(pointer), last(nullptr) {}

        _List_iterator(_node *pointer, _node *pointer_of_last) noexcept : current(pointer), last(pointer_of_last) {}

        _self __const_cast__() const noexcept { return *this; }

        reference operator*() const noexcept { return current == nullptr ? last->value_ : current->value_; }

        pointer operator->() const noexcept { return current == nullptr ? &last->value_ : &current->value_; }

        _self &operator++() noexcept {
            current = current->next_;
            return *this;
        }

        _self operator++(int) noexcept {
            _self tmp = *this;
            current = current->next_;
            return tmp;
        }

        _self &operator--() noexcept {
            if (current == nullptr && last != nullptr) {
                current = last;
                last = nullptr;
            } else
                current = current->prev_;
            return *this;
        }

        _self operator--(int) noexcept {
            _self tmp = *this;
            if (current == nullptr && last != nullptr) {
                current = last;
                last = nullptr;
            } else
                current = current->prev_;
            return tmp;
        }

        bool operator==(const _self &right) noexcept { return current == right.current; }

        bool operator!=(const _self &right) noexcept { return current != right.current; }
    };

    template <class Type> struct _List_const_iterator {
        typedef _List_const_iterator<Type> _self;
        typedef const _List_node<Type> _node;
        typedef _List_iterator<Type> interator;
        typedef Type *pointer;
        typedef Type &reference;

        _node *current;
        _node *last;

        _List_const_iterator() noexcept : current(nullptr), last(nullptr) {}

        _List_const_iterator(_node *pointer) noexcept : current(pointer), last(nullptr) {}

        _List_const_iterator(_node *pointer, _node *pointer_of_last) noexcept : current(pointer), last(pointer_of_last) {}

        _List_const_iterator(const interator &it) noexcept : current(it.current), last(it.last) {}

        interator __const_cast__() const noexcept { return interator(const_cast<_List_node<Type> *>(current)); }

        Type operator*() const noexcept { return current == nullptr ? last->value_ : current->value_; }

        pointer operator->() const noexcept { return static_cast<const pointer>(&(*this->__const_cast__())); }

        _self operator++() noexcept {
            current = current->next_;
            return *this;
        }

        _self operator++(int) noexcept {
            _self tmp = *this;
            current = current->next_;
            return tmp;
        }

        _self operator--() noexcept {
            current = current->prev_;
            return *this;
        }

        _self operator--(int) noexcept {
            _self tmp = *this;
            current = current->prev_;
            return tmp;
        }

        bool operator==(const _self &right) noexcept { return current == right.current; }

        bool operator!=(const _self &right) noexcept { return current != right.current; }
    };

    template <class Type> class list {
    public:
        typedef std::size_t size_type;
        typedef Type value_type;
        typedef _List_iterator<value_type> iterator;
        typedef _List_const_iterator<value_type> const_iterator;
        typedef value_type *pointer;
        typedef const value_type *const_pointer;
        typedef value_type &reference;
        typedef const value_type &const_reference;

    protected:
        typedef _List_node<value_type> _node;

        _node *first_, *last_;
        size_type size_;

        void __copy__(const list &other) noexcept {
            clear();
            if (other.first_ != nullptr)
                for (value_type elem : other) push_back(elem);
        }

        void __move__(list &&other) noexcept {
            clear();
            size_ = other.size_;
            first_ = other.first_;
            last_ = other.last_;
            other.size_ = 0;
            other.first_ = other.last_ = nullptr;
        }

    public:
        list() : first_(nullptr), last_(nullptr), size_(0) {}

        list(size_type count) : list() {
            value_type value;
            for (size_type i = 0; i < count; i++) push_back(value);
        }

        list(size_type count, const value_type &value) : list() {
            for (size_type i = 0; i < count; i++) push_back(value);
        }

        list(const list &other) : list() { __copy__(other); }

        list(list &&other) noexcept : list() { __move__(std::move(other)); }

        ~list() { clear(); }

        list &operator=(const list &right) {
            __copy__(right);
            return *this;
        }

        list &operator=(list &&right) noexcept {
            __move__(std::move(right));
            return *this;
        }

        iterator begin() { return iterator(first_, last_); }

        const_iterator begin() const { return const_iterator(first_, last_); }

        const_iterator cbegin() const noexcept { return const_iterator(first_, last_); }

        iterator end() { return iterator(nullptr, last_); }

        const_iterator end() const { return const_iterator(nullptr, last_); }

        const_iterator cend() const noexcept { return const_iterator(nullptr, last_); }

        void clear() {
            while (size_ > 0) pop_back();
        }

        void push_back(const value_type &value) { insert(end(), value); }

        void push_front(const value_type &value) { insert(begin(), value); }

        void pop_back() { erase(end()); }

        void pop_front() { erase(begin()); }

        reference front() { return first_->value_; }

        const_reference front() const { return static_cast<const_reference>(first_->value_); }

        reference back() { return last_->value_; }

        const_reference back() const { return static_cast<const_reference>(last_->value_); }

        iterator insert(const_iterator pos, const value_type &value) {
            _node *new_item = new _node(value);
            if (size_ == 0) first_ = last_ = new_item;
            else if (pos == begin()) {
                new_item->next_ = first_;
                first_->prev_ = new_item;
                first_ = new_item;
            } else if (pos == end()) {
                new_item->prev_ = last_;
                last_->next_ = new_item;
                last_ = new_item;
            } else {
                _node *prev = pos.current->prev_;
                _node *next = pos.__const_cast__().current;
                prev->next_ = new_item;
                new_item->prev_ = prev;
                next->prev_ = new_item;
                new_item->next_ = next;
            }
            size_++;
            return iterator(new_item);
        }

        iterator insert(const_iterator pos, const list<Type> &other) {
            iterator start_pos = pos.__const_cast__();
            for (Type elem : other) {
                insert(pos, elem);
                if (pos != end()) pos++;
            }
            return start_pos;
        }

        bool empty() const {
            if (first_ == nullptr) return true;
            return false;
        }

        iterator erase(const_iterator pos) {
            _node *res = nullptr;
            if (size_ == 0) return iterator(res);
            else if (size_ == 1) {
                delete first_;
                first_ = last_ = nullptr;
            } else if (pos == end() || pos.current == last_) {
                _node *temp = last_;
                last_ = last_->prev_;
                last_->next_ = nullptr;
                delete temp;
                res = last_;
            } else if (pos == begin()) {
                _node *temp = first_;
                first_ = first_->next_;
                first_->prev_ = nullptr;
                delete temp;
                res = size_ == 1 ? last_ : first_->next_;
            } else {
                _node *temp = pos.__const_cast__().current;
                temp->prev_->next_ = temp->next_;
                temp->next_->prev_ = temp->prev_;
                res = size_ == 1 ? last_ : temp->next_;
                delete temp;
            }
            size_--;
            return iterator(res);
        }

        void merge(list &other) {
            merge(std::move(other), [](const value_type &a, const value_type &b) { return a < b; });
        }

        void merge(list &&other) {
            merge(std::move(other), [](const value_type &a, const value_type &b) { return a < b; });
        }

        template <class Compare> void merge(list &other, Compare comp) { merge(std::move(other), comp); }

        template <class Compare> void merge(list &&other, Compare comp) {
            if (first_ == other.first_) return;
            list result;
            iterator iter_this = begin();
            iterator iter_other = other.begin();
            while (iter_this != end() && iter_other != other.end()) {
                if (comp(*iter_this, *iter_other)) {
                    result.push_back(*iter_this);
                    iter_this++;
                } else {
                    result.push_back(*iter_other);
                    iter_other++;
                }
            }
            while (iter_this != end()) {
                result.push_back(*iter_this);
                iter_this++;
            }
            while (iter_other != other.end()) {
                result.push_back(*iter_other);
                iter_other++;
            }
            other.clear();
            *this = std::move(result);
        }

        size_type size() const noexcept { return size_; }

        void sort() {
            sort([](const value_type &a, const value_type &b) { return a < b; });
        }

        template <class Compare> void sort(Compare comp) {
            if (size_ <= 1) return;
            list a, b;
            iterator it = this->begin();
            for (std::size_t i = 0; i < size_ / 2; i++) {
                a.push_back(*it);
                it++;
            }
            while (it != this->end()) {
                b.push_back(*it);
                it++;
            }
            a.sort(comp);
            b.sort(comp);
            a.merge(b, comp);
            *this = std::move(a);
        }
    };

    template <typename Type> class queue {
    public:
        typedef Type value_type;
        typedef std::size_t size_type;
        typedef value_type &reference;
        typedef const value_type &const_reference;

    protected:
        list<value_type> container;

    public:
        queue() : container() {}

        queue(const queue &other) : container(other.container) {}

        queue(queue &&other) noexcept : container(std::move(other.container)) {}

        queue &operator=(const queue &other) {
            container = other.container;
            return *this;
        }

        queue &operator=(queue &&other) noexcept {
            container = std::move(other.container);
            return *this;
        }

        reference front() { return container.front(); }

        const_reference front() const { return container.front(); }

        reference back() { return container.back(); }

        const_reference back() const { return container.back(); }

        bool empty() const { return container.empty(); }

        size_type size() const { return container.size(); }

        void push(const value_type &value) { container.push_back(value); }

        void pop() { container.pop_front(); }
    };
} // namespace utils

class RecordList;
class CodeRecordList;

class Record {
    friend RecordList;
    friend CodeRecordList;

public:
    static const uint16_t COUNT_OF_RECORDS;
    static const uint8_t AUTOR_LEN;
    static const uint8_t TITLE_LEN;
    static const uint8_t PUBLISH_LEN;
    static const uint8_t BITE_NUMBER;

private:
    char *author;
    char *title;
    char *publish;
    short year;
    short count_of_line;

    void __copy__(const Record &other) {
        for (std::size_t i = 0; i < AUTOR_LEN; i++)
            author[i] = other.author[i];
        for (std::size_t i = 0; i < TITLE_LEN; i++)
            title[i] = other.title[i];
        for (std::size_t i = 0; i < PUBLISH_LEN; i++)
            publish[i] = other.publish[i];

        year = other.year;
        count_of_line = other.count_of_line;
    }

protected:
    static void __getLastName__(char title[], char *last_name, std::size_t size) {
        int c = 0;
        int j = 0;
        for (int k = 0; k < 2; k++) {
            do { c = title[j++]; } while (c != ' ');
        }
        for (int i = 0; i < size; i++) last_name[i] = title[j++];
    }

public:
    Record() : year(0), count_of_line(0) {
        author = new char[AUTOR_LEN];
        title = new char[TITLE_LEN];
        publish = new char[PUBLISH_LEN];
    }

    Record(const Record &other) : Record::Record() { __copy__(other); }

    ~Record() {
        delete[] author;
        delete[] title;
        delete[] publish;
    }

    Record &operator=(const Record &other) {
        __copy__(other);
        return *this;
    }

    static RecordList getRecords(std::ifstream &file_base);

    static void printRecord(const Record &rec) { std::println("{} | {} | {} | {} | {}", rec.author, rec.title, rec.publish, rec.year, rec.count_of_line); }

    friend bool operator<(const Record &a, const Record &b);
    friend bool operator>(const Record &a, const Record &b);
    friend bool operator==(const Record &a, const Record &b);
    friend bool operator<=(const Record &a, const Record &b);
    friend bool operator>=(const Record &a, const Record &b);
    friend bool operator<(const Record &a, const short &b);
    friend bool operator>(const Record &a, const short &b);
    friend bool operator==(const Record &a, const short &b);
};

const uint16_t Record::COUNT_OF_RECORDS = 4000;
const uint8_t Record::AUTOR_LEN = 12;
const uint8_t Record::TITLE_LEN = 32;
const uint8_t Record::PUBLISH_LEN = 16;
const uint8_t Record::BITE_NUMBER = 3;

bool operator<(const Record &a, const Record &b) { return a.year < b.year; }

bool operator>(const Record &a, const Record &b) { return a.year > b.year; }

bool operator==(const Record &a, const Record &b) { return a.year == b.year; }

bool operator<=(const Record &a, const Record &b) { return a < b || a == b; }

bool operator>=(const Record &a, const Record &b) { return a > b || a == b; }

bool operator<(const Record &a, const short &b) { return a.year < b; }

bool operator>(const Record &a, const short &b) { return a.year > b; }

bool operator==(const Record &a, const short &b) { return a.year == b; }

class RecordList : public Record {
    utils::list<Record> record_list;
    std::unique_ptr<Record *> array_pointers;

    void __init_array__() {
        std::size_t i = 0;
        for (Record &record : record_list) array_pointers.get()[i++] = &record;
    }

public:
    RecordList() : record_list(COUNT_OF_RECORDS), array_pointers(new Record *[COUNT_OF_RECORDS]) { __init_array__(); }

    RecordList(const utils::list<Record> &l) : record_list(l), array_pointers(new Record *[COUNT_OF_RECORDS]) { __init_array__(); }

    RecordList(const RecordList &other) : RecordList() {
        record_list = other.record_list;
        __init_array__();
    }

    RecordList(RecordList &&other) noexcept {
        record_list = std::move(other.record_list);
        array_pointers = std::move(other.array_pointers);
    }

    RecordList &operator=(const utils::list<Record> &l) {
        record_list = l;
        __init_array__();
        return *this;
    }

    void sort() {
        const int count_of_queue = 256;
        for (int i = BITE_NUMBER - 1; i >= 0; i--) {
            utils::list<Record> Q[count_of_queue];
            for (auto &rec : record_list) {
                char last_name[BITE_NUMBER + 1] = { 0 };
                __getLastName__(rec.title, last_name, BITE_NUMBER + 1);
                int index = std::abs(last_name[i]) % count_of_queue;
                Q[index].push_back(rec);
            }
            record_list.clear();
            for (int j = count_of_queue - 1; j >= 0; j--) record_list.insert(record_list.cend(), Q[j]);
        }
        __init_array__();
    }

    void search(utils::queue<Record> &searched_records, const char *key) {
        std::size_t left = 0, right = COUNT_OF_RECORDS - 1, middle = 0;
        char last_name[BITE_NUMBER + 1] = { 0 };
        while (left < right) {
            middle = (left + right) / 2;
            __getLastName__(array_pointers.get()[middle]->title, last_name, BITE_NUMBER);
            if (strcmp(last_name, key) < 0) left = middle + 1;
            else right = middle;
        }
        __getLastName__(array_pointers.get()[right]->title, last_name, BITE_NUMBER);
        do {
            searched_records.push(*array_pointers.get()[right++]);
            __getLastName__(array_pointers.get()[right]->title, last_name, BITE_NUMBER);
        } while (strcmp(last_name, key) == 0 && right < COUNT_OF_RECORDS);
    }

    const utils::list<Record> &getRecordList() const { return record_list; }

    const std::unique_ptr<Record *> &getArrayPointers() const { return array_pointers; }
};

RecordList Record::getRecords(std::ifstream &file_base) {
    utils::list<Record> records(COUNT_OF_RECORDS);
    for (Record &rec : records) {
        file_base.read(rec.author, rec.AUTOR_LEN);
        file_base.read(rec.title, rec.TITLE_LEN);
        file_base.read(rec.publish, rec.PUBLISH_LEN);
        file_base.read((char *)&rec.year, sizeof(rec.year));
        file_base.read((char *)&rec.count_of_line, sizeof(rec.count_of_line));
    }
    return RecordList(records);
}

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
        for (std::size_t i = 0; i < size; ++i) sum += l[i].size();
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
        if (root == nullptr) root = new _TreeNode(val);
        else {
            _TreeNode<T> *cur = root, *pred = nullptr;
            do {
                pred = cur;
                if (val.front() < cur->value.front()) cur = cur->left;
                else cur = cur->right;
            } while (cur != nullptr);
            if (val.front() < pred->value.front()) pred->left = new _TreeNode(val);
            else pred->right = new _TreeNode(val);
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

class CodeRecordList {
    using code_type = utils::vector<int>;

    struct CodeTable {
        char symbol;
        float probability;
        std::size_t length_code;
        code_type code;
    };

    utils::list<Record> _origin_recs;
    utils::list<CodeTable> _alphabet;
    float _medium_length;
    float _entropy;

    bool _isExistInAlphabet(char symbol) {
        for (const CodeTable &code : _alphabet)
            if (code.symbol == symbol) return true;
        return false;
    }

    void _addProbability(char symbol) {
        for (CodeTable &code : _alphabet)
            if (code.symbol == symbol) ++code.probability;
    }

    void _addInAlphabet(char symbol) {
        if (!_isExistInAlphabet(symbol)) _alphabet.push_back({ symbol, 0.0f, 0, {} });
        else _addProbability(symbol);
    }

    void _codingAlphabet() {
        _alphabet.sort([](const CodeTable &a, const CodeTable &b) { return a.symbol < b.symbol; });
        utils::vector<float> q(_alphabet.size(), 0.0f);
        float pr = 0.0f;
        auto it = _alphabet.begin();
        for (std::size_t i = 0; i < _alphabet.size(); ++i) {
            q.at(i) = pr + it->probability / 2.0f;
            pr += it->probability;
            it->length_code = -std::log2(it->probability) + 1;
            _medium_length += it->probability * it->length_code;
            _entropy += it->probability * -std::log2(it->probability);
            ++it;
        }
        it = _alphabet.begin();
        for (std::size_t i = 0; i < _alphabet.size(); ++i) {
            it->code = utils::vector<int>(it->length_code, 0);
            for (std::size_t j = 0; j < it->length_code; ++j) {
                q.at(i) *= 2.0f;
                it->code.at(j) = q.at(i);
                if (q.at(i) > 1.0f) --q.at(i);
            }
            ++it;
        }
    }

    void _createAlphabet(std::ifstream &file) {
        std::size_t chars_number = 0;
        file.seekg(0);
        while (!file.eof()) {
            char c;
            file.read(&c, 1);
            _addInAlphabet(c);
            ++chars_number;
        }
        for (CodeTable &code : _alphabet) ++code.probability /= static_cast<float>(chars_number);
    }

public:
    CodeRecordList(std::ifstream &file) : _medium_length(0), _entropy(0) {
        _createAlphabet(file);
        _codingAlphabet();
    }

    void printCodeAlphabet() {
        std::println(" Char | Probability | Length Code | Code");
        for (const CodeTable &line : _alphabet) {
            std::print("{:5} | {:11f} | {:11} | ", line.symbol, line.probability, line.length_code);
            for (std::size_t i = 0; i < line.code.size(); ++i) std::print("{}", line.code.at(i));
            std::println();
        }
        std::println("\nSize: {}\n", _alphabet.size());
        std::println("\nMedium Length = {}", _medium_length);
        std::println("Entropy = {}", _entropy);
        std::println("Medium Length - Entropy = {}", _medium_length - _entropy);
    }
};

class Printer {
    static const uint8_t COUNT_LINE_OF_PAGE;
    static const uint16_t MAX_PAGE;

    static void clearConsole() {
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
        std::system("cls");
#else
        std::system("clear");
#endif
    }

public:
    static void printRecords(RecordList &records, std::ifstream &file_base) {
        uint8_t mode = 0;
        SetConsoleCP(866); // установка кодовой страницы win-cp 866 в поток ввода
        do {
            clearConsole();
            SetConsoleOutputCP(65001); // установка кодовой страницы win-cp 65001 в поток вывода
            std::println("Выберите режим просмотра:");
            std::println("1 - Просмотр по страницам");
            std::println("2 - Посмотреть все");
            std::println("3 - Найти записи");
            std::println("4 - Закодировать базу данных");
            std::println("0 - Выход");
            std::cin >> mode;
            switch (mode) {
                case '1':
                    printByPages(records);
                    break;
                case '2':
                    printAll(records);
                    break;
                case '3':
                    printSearchRecords(records);
                    break;
                case '4':
                    printCodeRecords(records, file_base);
                    break;
                default:
                    break;
            }
        } while (mode != '0');
    }

    static void printByPages(const RecordList &records) {
        uint8_t mode = 0;
        uint16_t page = 0;
        do {
            clearConsole();
            SetConsoleOutputCP(866);
            auto start_it = records.getRecordList().begin();
            for (uint16_t i = 0; i < page * COUNT_LINE_OF_PAGE; i++) start_it++;
            auto end_it = start_it;
            for (uint16_t i = 0; i < COUNT_LINE_OF_PAGE; i++) end_it++;
            for (auto it = start_it; it != end_it; it++) Record::printRecord(*it);
            std::println("{}/{}\n", page + 1, MAX_PAGE);
            SetConsoleOutputCP(65001);
            std::println("1 - Следующая страница");
            std::println("2 - Предыдущая страница");
            std::println("0 - Назад");
            std::cin >> mode;
            switch (mode) {
                case '1':
                    if (page < MAX_PAGE - 1) page++;
                    break;
                case '2':
                    if (page > 0) page--;
                    break;
                default:
                    break;
            }
        } while (mode != '0');
    }

    static void printAll(const RecordList &records) {
        SetConsoleOutputCP(866);
        for (const Record &rec : records.getRecordList()) Record::printRecord(rec);
        SetConsoleOutputCP(65001);
        char a = 0;
        std::println("\n0 - Назад");
        do { std::cin >> a; } while (a != '0');
    }

    static void printSearchRecords(RecordList &records) {
        SetConsoleOutputCP(65001);
        clearConsole();
        std::print("Введите первые {} буквы фамилии замечательного человека: ", Record::BITE_NUMBER);
        std::string key;
        std::cin >> key;
        std::println();
        utils::queue<Record> searched_records;
        records.search(searched_records, key.c_str());
        utils::list<Record> searched_records_copy;
        SetConsoleOutputCP(866);
        while (!searched_records.empty()) {
            Record::printRecord(searched_records.front());
            searched_records_copy.push_back(searched_records.front());
            searched_records.pop();
        }
        SetConsoleOutputCP(65001);
        char a = 0;
        std::println("\n1 - Поиск в дереве");
        std::println("0 - В начало");
        do { std::cin >> a; } while (a != '0' && a != '1');
        if (a == '1') printSearchTree(searched_records_copy);
    }

    static void printSearchTree(utils::list<Record> &records) {
        clearConsole();
        SetConsoleOutputCP(866);
        tree<Record> tree(records);
        tree.print(Record::printRecord);
        SetConsoleOutputCP(65001);
        std::print("\nВведите год: ");
        short key;
        std::cin >> key;
        std::println();
        records = std::move(tree.find(key));
        SetConsoleOutputCP(866);
        std::size_t i = 1;
        for (const Record &r : records) {
            std::print("{:3} - ", i++);
            Record::printRecord(r);
        }
        SetConsoleOutputCP(65001);
        char a = 0;
        std::println("\n0 - В начало");
        do { std::cin >> a; } while (a != '0');
    }

    static void printCodeRecords(const RecordList &records, std::ifstream &file_base) {
        clearConsole();
        SetConsoleOutputCP(866);
        CodeRecordList code_recs(file_base);
        code_recs.printCodeAlphabet();
        SetConsoleOutputCP(65001);
        char a = 0;
        std::println("0 - Назад");
        do { std::cin >> a; } while (a != '0');
    }
};

const uint8_t Printer::COUNT_LINE_OF_PAGE = 20;
const uint16_t Printer::MAX_PAGE = Record::COUNT_OF_RECORDS / Printer::COUNT_LINE_OF_PAGE;

int main() {
    int error_code = 0;
    const char *db_name = "testBase1.dat";
    std::ifstream file_base(db_name, std::ios_base::binary);
    if (file_base.is_open()) {
        RecordList records = Record::getRecords(file_base);
        records.sort();
        Printer::printRecords(records, file_base);
        file_base.close();
    } else std::println("File {} is not found!", db_name);
    return error_code;
}
