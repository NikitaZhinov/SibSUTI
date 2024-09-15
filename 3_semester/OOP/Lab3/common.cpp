#include "common.h"

Common::Point::Point() : x(0), y(0) {}

Common::Point::Point(const std::size_t &x, const std::size_t &y) : x(x), y(y) {}

Common::Point::Point(const Point &other) : Common::Point::Point() {
    __copy__(other);
}

Common::Point &Common::Point::operator=(const Point &other) {
    __copy__(other);
    return *this;
}

bool operator==(const Common::Point &left, const Common::Point &right) {
    return left.x == right.x && left.y == right.y;
}

void Common::Point::__copy__(const Point &other) {
    x = other.x;
    y = other.y;
}

const char *Common::input_file_name = "input.txt";

const char *Common::output_file_name = "output.txt";
