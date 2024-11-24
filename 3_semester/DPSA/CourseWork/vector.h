#pragma once

#include <utility>
#include <initializer_list>
#include <stdexcept>

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

        vector(std::initializer_list<value_type> init_list) : vector(init_list.size()) {
            size_type i = 0;
            for (value_type value : init_list) _values[i++] = value;
        }

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

        size_type size() noexcept { return _size; }

        size_type size() const noexcept { return _size; }
    };
} // namespace utils
