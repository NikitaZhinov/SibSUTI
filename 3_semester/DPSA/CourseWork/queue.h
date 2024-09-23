#pragma once

#include "list.h"

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
    /**
     * @brief Default constructor. Value-initializes the container.
     */
    queue() : container() {}

    /**
     * @brief Copy constructor.
     *
     * @param other - Another container adaptor to be used as source to initialize
     * the underlying container.
     */
    queue(const queue &other) : container(other.container) {}

    /**
     * @brief Move constructor.
     *
     * @param other - Another container adaptor to be used as source to initialize
     * the underlying container.
     */
    queue(queue &&other) noexcept : container(std::move(other.container)) {}

    /**
     * @brief Copy assignment operator. Replaces the contents with a copy of the
     * contents of other.
     *
     * @param other - Another container adaptor to be used as source to initialize
     * the underlying container.
     */
    queue &operator=(const queue &other) {
        container = other.container;
        return *this;
    }

    /**
     * @brief Move assignment operator. Replaces the contents with those of other
     * using move semantics.
     *
     * @param other - Another container adaptor to be used as source to initialize
     * the underlying container.
     */
    queue &operator=(queue &&other) noexcept {
        container = std::move(other.container);
        return *this;
    }

    /**
     * @brief Returns reference to the front element in the queue.
     *
     * @return Reference to the last element.
     */
    reference front() { return container.front(); }

    /**
     * @brief Returns reference to the front element in the queue.
     *
     * @return Reference to the last element.
     */
    const_reference front() const { return container.front(); }

    /**
     * @brief Returns reference to the back element in the queue.
     *
     * @return Reference to the last element.
     */
    reference back() { return container.back(); }

    /**
     * @brief Returns reference to the back element in the queue.
     *
     * @return Reference to the last element.
     */
    const_reference back() const { return container.back(); }

    /**
     * @brief Checks if the underlying container has no elements.
     *
     * @return True if the underlying container is empty, false otherwise.
     */
    bool empty() const { return container.empty(); }

    /**
     * @brief Returns the number of elements in the container adaptor.
     *
     * @return The number of elements in the container adaptor.
     */
    size_type size() const { return container.size(); }

    /**
     * @brief Pushes the given element value to the back of the queue.
     *
     * @param value - The value of the element to push.
     */
    void push(const value_type &value) { container.push_back(value); }

    /**
     * @brief Removes the front element from the queue.
     */
    void pop() { container.pop_front(); }

    /**
     * @brief Exchanges the contents of the container adaptor with those of other.
     *
     * @param other - Container adaptor to exchange the contents with.
     */
    void swap(queue &other) noexcept { container.swap(other.container); }

    template <class... Args>
    void insert_many_back(Args &&...args) {
        container.insert_many_back(args...);
    }
};
