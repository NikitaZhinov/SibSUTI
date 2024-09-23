#pragma once

#include <algorithm>
#include <limits>

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
    /**
     *  @brief Creates a list with no elements.
     *
     */
    list() : first_(nullptr), last_(nullptr), size_(0) {}

    /**
     * @brief Construct a new list object.
     *
     * @param count - The number of items in the new list.
     */
    list(size_type count) : list() {
        value_type value;
        for (size_type i = 0; i < count; i++) push_back(value);
    }

    /**
     * @brief Construct a new list object.
     *
     * @param count - The number of items in the new list.
     * @param value - The value that the list will be filled with.
     */
    list(size_type count, const value_type &value) : list() {
        for (size_type i = 0; i < count; i++) push_back(value);
    }

    /**
     * @brief Copy construct a new list object.
     *
     * @param other - The list to be copied.
     */
    list(const list &other) : list() { __copy__(other); }

    /**
     * @brief Move construct a new list object.
     *
     * @param other - The list to be moved.
     */
    list(list &&other) noexcept : list() { __move__(std::move(other)); }

    /**
     * @brief Constructs the container with the contents of the initializer list
     * init.
     *
     * @param init - Initializer list to initialize the elements of the container
     * with.
     */
    list(std::initializer_list<value_type> init) : list() {
        for (auto &elem : init) push_back(elem);
    }

    /**
     * @brief Destroy the list object.
     *
     */
    ~list() { clear(); }

    /**
     * @brief The copy operator.
     *
     * @param right - The list to be copied.
     * @return list&
     */
    list &operator=(const list &right) {
        __copy__(right);
        return *this;
    }

    /**
     * @brief The move operator.
     *
     * @param right - The list to be moved.
     * @return list&
     */
    list &operator=(list &&right) noexcept {
        __move__(std::move(right));
        return *this;
    }

    /**
     * @brief Returns an iterator to the first element.
     *
     * @return iterator
     */
    iterator begin() { return iterator(first_); }

    /**
     * @brief Returns a const iterator to the first element.
     *
     * @return iterator
     */
    const_iterator begin() const { return const_iterator(first_); }

    /**
     * @brief Returns a const iterator to the first element.
     *
     * @return iterator
     */
    const_iterator cbegin() const noexcept { return const_iterator(first_); }

    /**
     * @brief Returns an iterator to the last element.
     *
     * @return iterator
     */
    iterator end() { return iterator(nullptr, last_); }

    /**
     * @brief Returns a const iterator to the last element.
     *
     * @return iterator
     */
    const_iterator end() const { return const_iterator(nullptr, last_); }

    /**
     * @brief Returns a const iterator to the last element.
     *
     * @return iterator
     */
    const_iterator cend() const noexcept {
        return const_iterator(nullptr, last_);
    }

    /**
     * @brief Clears the list.
     *
     */
    void clear() {
        while (size_ > 0) pop_back();
    }

    /**
     * @brief Adds a new item to the end of the list.
     *
     * @param value - The new item.
     */
    void push_back(const value_type &value) { insert(end(), value); }

    /**
     * @brief Adds a new item to the top of the list.
     *
     * @param value - The new item
     */
    void push_front(const value_type &value) { insert(begin(), value); }

    /**
     * @brief Deletes the last item from the list.
     *
     */
    void pop_back() { erase(end()); }

    /**
     * @brief Deletes the first item from the list.
     *
     */
    void pop_front() { erase(begin()); }

    /**
     * @brief Replaces the contents of the container.
     *
     * @param count - The number of copies.
     * @param value - The value of copies.
     */
    void assign(size_type count, const_reference value) {
        clear();
        for (size_type i = 0; i < count; i++) push_back(value);
    }

    /**
     * @brief Replaces the content with items from another list.
     *
     * @param other - The another list.
     */
    void assign(list other) { *this = std::move(other); }

    /**
     * @brief Replaces the contents with copies of those in the range [first,
     * last].
     *
     * @tparam InputIterator
     * @param first - The iterator to the first item.
     * @param last - The iterator to the last item.
     */
    void assign(iterator first, iterator last) {
        clear();
        for (iterator it = first; it != last; it++) push_back(*it);
    }

    /**
     * @brief Returns a reference to the first element.
     *
     * @return reference The reference to the first element.
     */
    reference front() { return first_->value_; }

    /**
     * @brief Returns a const reference to the first element.
     *
     * @return const_reference The const reference to the first element.
     */
    const_reference front() const {
        return static_cast<const_reference>(first_->value_);
    }

    /**
     * @brief Returns a reference to the last element.
     *
     * @return reference The reference to the last element.
     */
    reference back() { return last_->value_; }

    /**
     * @brief Returns a const reference to the last element.
     *
     * @return const_reference The const reference to the last element.
     */
    const_reference back() const {
        return static_cast<const_reference>(last_->value_);
    }

    /**
     * @brief Inserts element at the specified location in the container.
     *
     * @param pos - The position in front of which the element will be placed.
     * @param value - The value of the element.
     * @return iterator
     */
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

    /**
     * @brief Inserts elements at the specified location in the container.
     *
     * @param pos - The position in front of which the elements will be placed.
     * @param count - The number of elements to insert.
     * @param value - The value of the elements.
     * @return iterator
     */
    iterator insert(const_iterator pos, size_type count, const value_type &value) {
        for (size_type i = 0; i < count; i++) insert(pos, value);
        return pos.__const_cast__();
    }

    /**
     * @brief Inserts elements at the specified location in the container.
     *
     * @param pos The position in front of which the elements will be placed.
     * @param first The iterator to the first item.
     * @param last The iterator to the last item.
     * @return iterator
     */
    iterator insert(const_iterator pos, iterator first, iterator last) {
        iterator start_pos = pos.__const_cast__();
        for (iterator it = first; it != last; it++) {
            insert(pos, *it);
            if (pos != end()) pos++;
        }
        return start_pos;
    }

    /**
     * @brief Inserts elements at the specified location in the container.
     *
     * @param pos - The position in front of which the elements will be placed.
     * @param other - The another list.
     * @return iterator
     */
    iterator insert(const_iterator pos, list<Type> other) {
        iterator start_pos = pos.__const_cast__();
        for (Type elem : other) {
            insert(pos, elem);
            if (pos != end()) pos++;
        }
        return start_pos;
    }

    /**
     * @brief Checks if the list is empty.
     *
     * @return true
     * @return false
     */
    bool empty() const {
        if (first_ == nullptr) return true;
        return false;
    }

    /**
     * @brief Erases the specified element from the container.
     *
     * @param pos - Removes the element at pos.
     * @return iterator
     */
    iterator erase(const_iterator pos) {
        _node *res = nullptr;
        if (size_ == 0) {
        } else if (size_ == 1) {
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

    /**
     * @brief Erases the specified elements from the container in the range
     * [first, last).
     *
     * @param first - The iterator to the first item.
     * @param last - The iterator to the last item.
     * @return iterator
     */
    iterator erase(const_iterator first, const_iterator last) {
        iterator res;
        for (const_iterator it = first; it != last;) res = erase(it++);
        return res;
    }

    /**
     * @brief Returns the maximum number of elements the container.
     *
     * @return size_type
     */
    size_type max_size() const {
        return static_cast<size_type>((std::numeric_limits<size_type>::max)()) /
               sizeof(_node) /
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__)
               1;
#else
               2;
#endif
    }

    /**
     * @brief The function does nothing if other refers to the same object as
     * *this. Otherwise, merges other into *this. Both lists should be sorted. No
     * elements are copied, and the container other becomes empty after the merge.
     * This operation is stable: for equivalent elements in the two lists, the
     * elements from *this always precede the elements from other, and the order
     * of equivalent elements of *this and other does not change.
     *
     * @param other - The another list.
     */
    void merge(list &other) {
        merge(std::move(other),
              [](const value_type &a, const value_type &b) { return a < b; });
    }

    /**
     * @brief The function does nothing if other refers to the same object as
     * *this. Otherwise, merges other into *this. Both lists should be sorted. No
     * elements are copied, and the container other becomes empty after the merge.
     * This operation is stable: for equivalent elements in the two lists, the
     * elements from *this always precede the elements from other, and the order
     * of equivalent elements of *this and other does not change.
     *
     * @param other - The another list.
     */
    void merge(list &&other) {
        merge(std::move(other),
              [](const value_type &a, const value_type &b) { return a < b; });
    }

    /**
     * @brief  The function does nothing if other refers to the same object as
     * *this. Otherwise, merges other into *this. Both lists should be sorted. No
     * elements are copied, and the container other becomes empty after the merge.
     * This operation is stable: for equivalent elements in the two lists, the
     * elements from *this always precede the elements from other, and the order
     * of equivalent elements of *this and other does not change.
     *
     * @tparam Compare must meet the requirements of Compare
     * (https://en.cppreference.com/w/cpp/named_req/Compare).
     * @param other - The another list.
     * @param comp - comparison function object (i.e. an object that satisfies the
     * requirements of Compare) which returns ​true if the first argument is
     * less than (i.e. is ordered before) the second.
     */
    template <class Compare>
    void merge(list &other, Compare comp) {
        merge(std::move(other), comp);
    }

    /**
     * @brief  The function does nothing if other refers to the same object as
     * *this. Otherwise, merges other into *this. Both lists should be sorted. No
     * elements are copied, and the container other becomes empty after the merge.
     * This operation is stable: for equivalent elements in the two lists, the
     * elements from *this always precede the elements from other, and the order
     * of equivalent elements of *this and other does not change.
     *
     * @tparam Compare must meet the requirements of Compare
     * (https://en.cppreference.com/w/cpp/named_req/Compare).
     * @param other - The another list.
     * @param comp - comparison function object (i.e. an object that satisfies the
     * requirements of Compare) which returns ​true if the first argument is
     * less than (i.e. is ordered before) the second.
     */
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

    /**
     * @brief Removes all elements that are equal to value.
     *
     * @param value - Value of the elements to remove.
     * return size_type - The number of elements removed.
     */
    size_type remove(const value_type &value) {
        return remove_if([&](const value_type &val) { return val == value; });
    }

    /**
     * @brief Removes all elements for which predicate p returns true.
     *
     * @param p - Unary predicate which returns ​true if the element should be.
     * removed. return size_type The number of elements removed.
     */
    template <class UnaryPredicate>
    size_type remove_if(UnaryPredicate p) {
        size_type n = 0;
        _node *cur = first_;
        while (cur != nullptr) {
            if (p(cur->value_)) {
                _node *del = cur;
                cur = cur->next_;
                erase(iterator(del));
                n++;
                continue;
            }
            cur = cur->next_;
        }
        return n;
    }

    /**
     * @brief Resizes the container to contain count elements.
     * If the current size is greater than count, the container is reduced to its
     * first count elements. If the current size is less than count, additional
     * default-inserted elements are appended.
     *
     * @param cout - New size of the container.
     */
    void resize(size_type count) {
        Type val {};
        resize(count, val);
    }

    /**
     * @brief Resizes the container to contain count elements.
     * If the current size is greater than count, the container is reduced to its
     * first count elements. If the current size is less than count, additional
     * copies of value are appended.
     *
     * @param cout - New size of the container.
     * @param value - The value to initialize the new elements with.
     */
    void resize(size_type count, const value_type &value) {
        if (count == size_) return;
        while (count > size_) push_back(value);
        while (count < size_) pop_back();
    }

    /**
     * @brief Reverses the order of the elements in the container. No references
     * or iterators become invalidated.
     *
     */
    void reverse() noexcept {
        iterator left = first_;
        iterator right = last_;

        while (left != right && left.current->prev_ != right.current) {
            Type temp = *left;
            *left = *right;
            *right = temp;
            left++;
            right--;
        }
    }

    /**
     * @brief Returns the number of elements in the container.
     *
     */
    size_type size() const noexcept { return size_; }

    /**
     * @brief Sorts the elements and preserves the order of equivalent elements.
     * No references or iterators become invalidated.
     * Elements are compared using operator<.
     *
     */
    void sort() {
        sort([](const value_type &a, const value_type &b) { return a < b; });
    }

    /**
     * @brief Sorts the elements and preserves the order of equivalent elements.
     * No references or iterators become invalidated.
     * Elements are compared using comp.
     *
     * @tparam Compare - must meet the requirements of Compare
     * (https://en.cppreference.com/w/cpp/named_req/Compare).
     *
     * @param comp - Comparison function object (i.e. an object that satisfies the
     * requirements of Compare) which returns ​true if the first argument is
     * less than (i.e. is ordered before) the second. The signature of the
     * comparison function should be equivalent to the following: bool cmp(const
     * Type1& a, const Type2& b);
     *
     */
    template <class Compare>
    void sort(Compare comp) {
        if (this->empty() || size_ == 1) return;

        list a, b, c0, c1;

        // split
        bool f = true;
        for (Type elem : *this) {
            if (f)
                a.push_back(elem);
            else
                b.push_back(elem);
            f = !f;
        }

        size_type size_list = 1, size_a = 0, size_b = 0;
        while (size_list < size_) {
            c0.clear();
            c1.clear();

            int i = 0;
            size_type m = size_;
            while (m > 0) {
                if (m >= size_list)
                    size_a = size_list;
                else
                    size_a = m;
                m -= size_a;
                if (m >= size_list)
                    size_b = size_list;
                else
                    size_b = m;
                m -= size_b;

                list c = std::move(i == 0 ? c0 : c1);

                // merge
                iterator it_a = a.begin(), it_b = b.begin();
                while (size_a > 0 && size_b > 0) {
                    if (comp(*it_a, *it_b)) {
                        c.push_back(*it_a);
                        it_a++;
                        size_a--;
                    } else {
                        c.push_back(*it_b);
                        it_b++;
                        size_b--;
                    }
                }
                while (size_a > 0) {
                    c.push_back(*it_a);
                    it_a++;
                    size_a--;
                }
                while (size_b > 0) {
                    c.push_back(*it_b);
                    it_b++;
                    size_b--;
                }

                if (i == 0)
                    c0 = std::move(c);
                else
                    c1 = std::move(c);

                i = 1 - i;
            }

            a = std::move(c0);
            b = std::move(c1);
            size_list *= 2;
        }

        *this = std::move(c0);
    }

    /**
     * @brief Transfers all elements from other into *this. The elements are
     * inserted before the element pointed to by pos. The container other becomes
     * empty after the operation.
     *
     * @param pos - Element before which the content will be inserted.
     * @param other - Another container to transfer the content from.
     */
    void splice(const_iterator pos, list &other) {
        insert(pos, other);
        other.clear();
    }

    /**
     * @brief Transfers all elements from other into *this. The elements are
     * inserted before the element pointed to by pos. The container other becomes
     * empty after the operation.
     *
     * @param pos - Element before which the content will be inserted.
     * @param other - Another container to transfer the content from.
     */
    void splice(const_iterator pos, list &&other) { splice(pos, other); }

    /**
     * @brief Transfers the element pointed to by it from other into *this. The
     * element is inserted before the element pointed to by pos.
     *
     * @param pos - Element before which the content will be inserted.
     * @param other - Another container to transfer the content from.
     * @param it - The element to transfer from other to *this.
     */
    void splice(const_iterator pos, list &other, const_iterator it) {
        insert(pos, *it);
        other.erase(it);
    }

    /**
     * @brief Transfers the element pointed to by it from other into *this. The
     * element is inserted before the element pointed to by pos.
     *
     * @param pos - Element before which the content will be inserted.
     * @param other - Another container to transfer the content from.
     * @param it - The element to transfer from other to *this.
     */
    void splice(const_iterator pos, list &&other, const_iterator it) {
        splice(pos, other, it);
    }

    /**
     * @brief Transfers the elements in the range [first, last) from other into
     * *this. The elements are inserted before the element pointed to by pos.
     *
     * @param pos - Element before which the content will be inserted.
     * @param other - Another container to transfer the content from.
     * @param first, last - The range of elements to transfer from other to *this.
     */
    void splice(const_iterator pos, list &other, const_iterator first, const_iterator last) {
        insert(pos, first.__const_cast__(), last.__const_cast__());
        other.erase(first, last);
    }

    /**
     * @brief Transfers the elements in the range [first, last) from other into
     * *this. The elements are inserted before the element pointed to by pos.
     *
     * @param pos - Element before which the content will be inserted.
     * @param other - Another container to transfer the content from.
     * @param first, last - The range of elements to transfer from other to *this.
     */
    void splice(const_iterator pos, list &&other, const_iterator first, const_iterator last) {
        splice(pos, other, first, last);
    }

    /**
     * @brief Exchanges the contents of the container with those of other.
     *
     * @param other - Container to exchange the contents with.
     */
    void swap(list &right) noexcept {
        list temp = std::move(*this);
        *this = std::move(right);
        right = std::move(temp);
    }

    /**
     * @brief Removes all consecutive duplicate elements from the container.
     *
     * @return size_type - The number of elements removed.
     */
    size_type unique() {
        return unique(
            [](const value_type &a, const value_type &b) { return a == b; });
    }

    /**
     * @brief Removes all consecutive duplicate elements from the container.
     *
     * @tparam BinaryPredicate - must meet the requirements of BinaryPredicate
     * (https://en.cppreference.com/w/cpp/named_req/BinaryPredicate).
     *
     * @param - binary predicate which returns ​true if the elements should be
     * treated as equal. The signature of the predicate function should be
     * equivalent to the following: bool pred(const Type1 &a, const Type2 &b);
     *
     * @return size_type - The number of elements removed.
     */
    template <class BinaryPredicate>
    size_type unique(BinaryPredicate p) {
        list temp;
        size_type n = 0;

        auto is_exist = [&](const value_type &elem) {
            for (value_type &e : temp)
                if (p(e, elem)) return true;
            return false;
        };

        for (value_type &elem : *this)
            if (!is_exist(elem)) temp.push_back(elem);
        *this = std::move(temp);

        return n;
    }

    template <class... Args>
    iterator insert_many(const_iterator pos, Args &&...args) {
        iterator it;
        for (const auto &arg : { args... }) it = insert(pos, arg);
        return it;
    }

    template <class... Args>
    void insert_many_front(Args &&...args) {
        insert_many(begin(), args...);
    }

    template <class... Args>
    void insert_many_back(Args &&...args) {
        insert_many(end(), args...);
    }
};
