#include "point.h"

Point::Point() : x(0), y(0) {}

Point::Point(const std::size_t &x, const std::size_t &y) : x(x), y(y) {}

Point::Point(const Point &other) : Point::Point() {
    __copy__(other);
}

Point &Point::operator=(const Point &other) {
    __copy__(other);
    return *this;
}

bool operator==(const Point &left, const Point &right) {
    return left.x == right.x && left.y == right.y;
}

void Point::__copy__(const Point &other) {
    x = other.x;
    y = other.y;
}
