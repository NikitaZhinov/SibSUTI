#pragma once

#include <string>
#include <print>
#include <fstream>
#include <string>
#include <list>
#include <vector>

class Common {
public:
    struct Point {
        std::size_t x, y;

        Point();
        Point(const std::size_t &x, const std::size_t &y);
        Point(const Point &other);

        Point &operator=(const Point &other);
        friend bool operator==(const Point &left, const Point &right);

    private:
        void __copy__(const Point &other);
    };

    static const char *input_file_name;
    static const char *output_file_name;
};
