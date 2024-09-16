#pragma once

#include "common.h"
#include "animal.h"

struct ModelParams {
    Common::Point map_size;
    std::size_t step_number;

    std::list<Rabbit> rabbits;
    std::list<Fox> foxes;

    ModelParams();
};

class Model {
    ModelParams params;
    std::vector<std::vector<int64_t>> map;

public:
    Model(const ModelParams &params);
    Model(const Model &other);

    std::vector<std::vector<int64_t>> &start();
    void step();
};
