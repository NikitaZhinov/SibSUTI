#pragma once

#include <algorithm>
#include <limits>

namespace utils {
    template <class Type>
    struct _List_node {
        _List_node *next_, *prev_;
        Type value_;

        _List_node(const Type &value) : next_(nullptr), prev_(nullptr), value_(value) {}
    };

    template <class Type>
    struct _List_iterator {
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

        reference operator*() const noexcept {
            return current == nullptr ? last->value_ : current->value_;
        }

        pointer operator->() const noexcept {
            return current == nullptr ? &last->value_ : &current->value_;
        }

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

        bool operator==(const _self &right) noexcept {
            return current == right.current;
        }

        bool operator!=(const _self &right) noexcept {
            return current != right.current;
        }
    };

    template <class Type>
    struct _List_const_iterator {
        typedef _List_const_iterator<Type> _self;
        typedef const _List_node<Type> _node;
        typedef _List_iterator<Type> interator;
        typedef Type *pointer;
        typedef Type &reference;

        _node *current;
        _node *last;

        _List_const_iterator() noexcept : current(nullptr), last(nullptr) {}

        _List_const_iterator(_node *pointer) noexcept
            : current(pointer), last(nullptr) {}

        _List_const_iterator(_node *pointer, _node *pointer_of_last) noexcept
            : current(pointer), last(pointer_of_last) {}

        _List_const_iterator(const interator &it) noexcept
            : current(it.current), last(it.last) {}

        interator __const_cast__() const noexcept {
            return interator(const_cast<_List_node<Type> *>(current));
        }

        Type operator*() const noexcept {
            return current == nullptr ? last->value_ : current->value_;
        }

        pointer operator->() const noexcept {
            return static_cast<const pointer>(&(*this->__const_cast__()));
        }

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

        bool operator==(const _self &right) noexcept {
            return current == right.current;
        }

        bool operator!=(const _self &right) noexcept {
            return current != right.current;
        }
    };

    template <class Type>
    class list {
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
            if (size_ == 0)
                first_ = last_ = new_item;
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
            merge(std::move(other),
                  [](const value_type &a, const value_type &b) { return a < b; });
        }

        void merge(list &&other) {
            merge(std::move(other),
                  [](const value_type &a, const value_type &b) { return a < b; });
        }

        template <class Compare>
        void merge(list &other, Compare comp) {
            merge(std::move(other), comp);
        }

        template <class Compare>
        void merge(list &&other, Compare comp) {
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

        template <class Compare>
        void sort(Compare comp) {
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

} // namespace utils
