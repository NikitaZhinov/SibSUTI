#pragma once

#include "model.h"

class RWer {
    static const char *input_file_name;
    static const char *output_file_name;

public:
    static void getInput(ModelParams &model);
    static void printMap(const std::vector<std::vector<long long>> &map);
};
