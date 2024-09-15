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
    std::vector<std::vector<long long>> map;

public:
    Model(const ModelParams &params);
    Model(const Model &other);

    std::vector<std::vector<long long>> &start();
    void step();
};
