#pragma once

#include <cstdlib>

struct Point {
    std::size_t x, y;

    Point();
    Point(const std::size_t &x, const std::size_t &y);
    Point(const Point &other);

    ~Point() = default;

    Point &operator=(const Point &other);
    friend bool operator==(const Point &left, const Point &right);

private:
    void __copy__(const Point &other);
};
