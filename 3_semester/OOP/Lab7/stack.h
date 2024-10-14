#pragma once

#include "list.h"

template <typename Type> class stack : private list<Type> {
public:
	typedef Type value_type;
	typedef std::size_t size_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;

public:
	stack() = default;

	stack(const stack& other) { this->__copy__(other); }

	stack(stack&& other) noexcept { this->__move__(std::move(other)); }

	stack& operator=(const stack& other) {
		this->__copy__(other);
		return *this;
	}

	stack& operator=(stack&& other) noexcept {
		this->__move__(std::move(other));
		return *this;
	}

	reference top() { return list<Type>::back(); }

	const_reference top() const { return list<Type>::back(); }

	bool empty() const { return list<Type>::empty(); }

	size_type size() const { return list<Type>::size(); }

	static size_type max_size() { return max_size(); }

	void push(const value_type& value) { this->push_back(value); }

	void pop() { this->pop_back(); }

	void swap(stack& other) noexcept { list<Type>::swap(*this, other); }

	static void swap(stack& left, stack& right) noexcept { list<Type>::swap(left, right); }
};

