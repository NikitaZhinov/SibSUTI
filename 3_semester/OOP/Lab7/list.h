#pragma once

#include <algorithm>
#include <limits>

template <class Type> struct _List_node {
	_List_node* next_, * prev_;
	Type value_;

	_List_node(const Type& value) : next_(nullptr), prev_(nullptr), value_(value) {}
};

template <class Type> struct _List_iterator {
	using _self = _List_iterator<Type>;
	using _node = _List_node<Type>;
	using pointer = Type*;
	using reference = Type&;

	_node* current;
	_node* last;

	_List_iterator() noexcept : current(nullptr), last(nullptr) {}

	_List_iterator(_node* pointer) noexcept : current(pointer), last(nullptr) {}

	_List_iterator(_node* pointer, _node* pointer_of_last) noexcept : current(pointer), last(pointer_of_last) {}

	_self __const_cast__() const noexcept { return *this; }

	reference operator*() const noexcept { return current == nullptr ? last->value_ : current->value_; }

	pointer operator->() const noexcept { return current == nullptr ? &last->value_ : &current->value_; }

	_self& operator++() noexcept {
		current = current->next_;
		return *this;
	}

	_self operator++(int) noexcept {
		_self tmp = *this;
		current = current->next_;
		return tmp;
	}

	_self& operator--() noexcept {
		current = current->prev_;
		return *this;
	}

	_self operator--(int) noexcept {
		_self tmp = *this;
		current = current->prev_;
		return tmp;
	}

	friend bool operator==(const _self& left, const _self& right) noexcept { return left.current == right.current; }

	friend bool operator!=(const _self& left, const _self& right) noexcept { return left.current != right.current; }
};

template <class Type> struct _List_const_iterator {
	using _self = _List_const_iterator<Type>;
	using _node = const _List_node<Type>;
	using interator = _List_iterator<Type>;
	using pointer = Type*;
	using reference = Type&;

	_node* current;
	_node* last;

	_List_const_iterator() noexcept : current(nullptr), last(nullptr) {}

	_List_const_iterator(_node* pointer) noexcept : current(pointer), last(nullptr) {}

	_List_const_iterator(_node* pointer, _node* pointer_of_last) noexcept : current(pointer), last(pointer_of_last) {}

	_List_const_iterator(const interator& it) noexcept : current(it.current), last(it.last) {}

	interator __const_cast__() const noexcept { return interator(const_cast<_List_node<Type> *>(current)); }

	Type operator*() const noexcept { return current == nullptr ? last->value_ : current->value_; }

	pointer operator->() const noexcept { return static_cast<const pointer>(&(*this->__const_cast__())); }

	_self& operator++() noexcept {
		current = current->next_;
		return *this;
	}

	_self operator++(int) noexcept {
		_self tmp = *this;
		current = current->next_;
		return tmp;
	}

	_self& operator--() noexcept {
		current = current->prev_;
		return *this;
	}

	_self operator--(int) noexcept {
		_self tmp = *this;
		current = current->prev_;
		return tmp;
	}

	friend bool operator==(const _self& left, const _self& right) noexcept { return left.current == right.current; }

	friend bool operator!=(const _self& left, const _self& right) noexcept { return left.current != right.current; }
};

template <class Type> class list {
public:
	using size_type = std::size_t;
	using value_type = Type;
	using iterator = _List_iterator<value_type>;
	using const_iterator = _List_const_iterator<value_type>;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

protected:
	using _node = _List_node<value_type>;

	_node* first_, * last_;
	size_type size_;

	void __copy__(const list& other) {
		clear();
		if (other.first_ != nullptr)
			for (const_reference elem : other) push_back(elem);
	}

	void __move__(list&& other) noexcept {
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

	list(size_type count, const value_type& value) : list() {
		for (size_type i = 0; i < count; i++) push_back(value);
	}

	list(const list& other) : list() { __copy__(other); }

	list(list&& other) noexcept : list() { __move__(std::move(other)); }

	list(std::initializer_list<value_type> init) : list() {
		for (auto& elem : init) push_back(elem);
	}

	~list() { clear(); }

	list& operator=(const list& right) {
		__copy__(right);
		return *this;
	}

	list& operator=(list&& right) noexcept {
		__move__(std::move(right));
		return *this;
	}

	iterator begin() { return iterator(first_); }

	const_iterator begin() const { return const_iterator(first_); }

	const_iterator cbegin() const noexcept { return const_iterator(first_); }

	iterator end() { return iterator(nullptr, last_); }

	const_iterator end() const { return const_iterator(nullptr, last_); }

	const_iterator cend() const noexcept { return const_iterator(nullptr, last_); }

	void clear() { while (size_ > 0) pop_back(); }

	void push_back(const value_type& value) { insert(end(), value); }

	void push_front(const value_type& value) { insert(begin(), value); }

	void pop_back() { erase(end()); }

	void pop_front() { erase(begin()); }

	void assign(size_type count, const_reference value) {
		clear();
		for (size_type i = 0; i < count; i++) push_back(value);
	}

	void assign(list other) { *this = std::move(other); }

	void assign(iterator first, iterator last) {
		clear();
		for (iterator it = first; it != last; it++) push_back(*it);
	}

	reference front() { return first_->value_; }

	const_reference front() const { return static_cast<const_reference>(first_->value_); }

	reference back() { return last_->value_; }

	const_reference back() const { return static_cast<const_reference>(last_->value_); }

	iterator insert(const_iterator pos, const value_type& value) {
		_node* new_item;
		try { new_item = new _node(value); }
		catch (std::bad_alloc& ba) { throw ba.what(); }

		if (size_ == 0) first_ = last_ = new_item;
		else if (pos == begin()) {
			new_item->next_ = first_;
			first_->prev_ = new_item;
			first_ = new_item;
		}
		else if (pos == end()) {
			new_item->prev_ = last_;
			last_->next_ = new_item;
			last_ = new_item;
		}
		else {
			_node* prev = pos.current->prev_;
			_node* next = pos.__const_cast__().current;
			prev->next_ = new_item;
			new_item->prev_ = prev;
			next->prev_ = new_item;
			new_item->next_ = next;
		}
		size_++;
		return iterator(new_item);
	}

	iterator insert(const_iterator pos, size_type count, const value_type& value) {
		for (size_type i = 0; i < count; i++) insert(pos, value);
		return pos.__const_cast__();
	}

	iterator insert(const_iterator pos, iterator first, iterator last) {
		iterator start_pos = pos.__const_cast__();
		for (iterator it = first; it != last; it++) {
			insert(pos, *it);
			if (pos != end()) pos++;
		}
		return start_pos;
	}

	iterator insert(const_iterator pos, list<Type> other) {
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
		_node* res = nullptr;
		if (size_ == 0)	throw std::underflow_error("The list is empty!");
		else if (size_ == 1) {
			delete first_;
			first_ = last_ = nullptr;
		}
		else if (pos == end() || pos.current == last_) {
			_node* temp = last_;
			last_ = last_->prev_;
			last_->next_ = nullptr;
			delete temp;
			res = last_;
		}
		else if (pos == begin()) {
			_node* temp = first_;
			first_ = first_->next_;
			first_->prev_ = nullptr;
			delete temp;
			res = size_ == 1 ? last_ : first_->next_;
		}
		else {
			_node* temp = pos.__const_cast__().current;
			temp->prev_->next_ = temp->next_;
			temp->next_->prev_ = temp->prev_;
			res = size_ == 1 ? last_ : temp->next_;
			delete temp;
		}
		size_--;
		return iterator(res);
	}

	iterator erase(const_iterator first, const_iterator last) {
		iterator res;
		for (const_iterator it = first; it != last;) res = erase(it++);
		return res;
	}

	static size_type max_size() {
		return static_cast<size_type>((std::numeric_limits<size_type>::max)()) / sizeof(_node);
	}

	void merge(list& other) { merge(std::move(other), [](const value_type& a, const value_type& b) { return a <= b; }); }

	void merge(list&& other) { merge(std::move(other), [](const value_type& a, const value_type& b) { return a <= b; }); }

	template <class Compare> void merge(list& other, Compare comp) { merge(std::move(other), comp); }

	template <class Compare> void merge(list&& other, Compare comp) {
		if (first_ == other.first_) return;

		list result;

		iterator iter_this = begin();
		iterator iter_other = other.begin();

		while (iter_this != end() && iter_other != other.end()) {
			if (comp(*iter_this, *iter_other)) {
				result.push_back(*iter_this);
				iter_this++;
			}
			else {
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

	size_type remove(const value_type& value) { return remove_if([&](const value_type& val) { return val == value; }); }

	template <class UnaryPredicate>	size_type remove_if(UnaryPredicate p) {
		size_type n = 0;
		_node* cur = first_;
		while (cur != nullptr) {
			if (p(cur->value_)) {
				_node* del = cur;
				cur = cur->next_;
				erase(iterator(del));
				n++;
			}
			else cur = cur->next_;
		}
		return n;
	}

	void resize(size_type count) {
		Type val{};
		resize(count, val);
	}

	void resize(size_type count, const value_type& value) {
		if (count == size_) return;
		while (count > size_) push_back(value);
		while (count < size_) pop_back();
	}

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

	size_type size() const noexcept { return size_; }

	void sort() { sort(*this, [](const_reference a, const_reference b) { return a <= b; }); }

	template <class Compare> void sort(Compare comp) { sort(*this, [](const_reference a, const_reference b) { return a <= b; }); }

	static void sort(list& l) { sort(l, [](const_reference a, const_reference b) { return a <= b; }); }

	template <class Compare> static void sort(list& l, Compare comp) {
		if (l.size_ <= 1) return;

		list a, b;

		iterator it = l.begin();
		for (std::size_t i = 0; i < l.size_ / 2; i++) {
			a.push_back(*it);
			it++;
		}
		while (it != l.end()) {
			b.push_back(*it);
			it++;
		}

		a.sort();
		b.sort();

		a.merge(b, comp);
		l = std::move(a);
	}

	void splice(const_iterator pos, list& other) {
		insert(pos, other);
		other.clear();
	}

	void splice(const_iterator pos, list&& other) { splice(pos, other); }

	void splice(const_iterator pos, list& other, const_iterator it) {
		insert(pos, *it);
		other.erase(it);
	}

	void splice(const_iterator pos, list&& other, const_iterator it) { splice(pos, other, it); }

	void splice(const_iterator pos, list& other, const_iterator first, const_iterator last) {
		insert(pos, first.__const_cast__(), last.__const_cast__());
		other.erase(first, last);
	}

	void splice(const_iterator pos, list&& other, const_iterator first, const_iterator last) { splice(pos, other, first, last); }

	void swap(list& right) noexcept {
		swap(*this, right);
	}

	static void swap(list& left, list& right) noexcept {
		list temp = std::move(left);
		left = std::move(right);
		right = std::move(temp);
	}

	size_type unique() { return unique(*this, [](const value_type& a, const value_type& b) { return a == b; }); }

	template <class BinaryPredicate> size_type unique(BinaryPredicate p) { return unique(*this, p); }

	static size_type unique(list& l) { return unique(l, [](const value_type& a, const value_type& b) { return a == b; }); }

	template <class BinaryPredicate> static size_type unique(list& l, BinaryPredicate p) {
		list temp;
		size_type n = 0;

		auto is_exist = [&](const value_type& elem) {
			for (value_type& e : temp) if (p(e, elem)) return true;
			return false;
			};

		for (value_type& elem : *this) if (!is_exist(elem)) temp.push_back(elem);
		*this = std::move(temp);

		return n;
	}
};
