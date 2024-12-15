#pragma once

#include "list.h"

namespace utils {
    template <typename Type>
    class queue {
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
