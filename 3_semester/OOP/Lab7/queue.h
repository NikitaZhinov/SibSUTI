#pragma once

#include "list.h"

template <typename Type> class queue : private list<Type> {
public:
	typedef Type value_type;
	typedef std::size_t size_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;

public:
	queue() = default;

	queue(const queue& other) { this->__copy__(other); }

	queue(queue&& other) noexcept { this->__move__(std::move(other)); }

	queue& operator=(const queue& other) {
		this->__copy__(other);
		return *this;
	}

	queue& operator=(queue&& other) noexcept {
		this->__move__(std::move(other));
		return *this;
	}

	reference front() { return list<Type>::front(); }

	const_reference front() const { return list<Type>::front(); }

	reference back() { return list<Type>::back(); }

	const_reference back() const { return list<Type>::back(); }

	bool empty() const { return list<Type>::empty(); }

	size_type size() const { return list<Type>::size(); }

	static size_type max_size() { return max_size(); }

	void push(const value_type& value) { this->push_back(value); }

	void pop() { this->pop_front(); }

	void swap(queue& other) noexcept { list<Type>::swap(other); }

	static void swap(queue& left, queue& right) noexcept { list<Type>::swap(left, right); }
};
