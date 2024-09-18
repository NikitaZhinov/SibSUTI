#pragma once

#include "point.h"
#include "animal.h"

#include <list>
#include <vector>

struct ModelParams {
    Point map_size;
    std::size_t step_number;

    std::list<Rabbit> rabbits;
    std::list<Fox> foxes;

    ModelParams();
};

class Model {
    ModelParams params;
    std::vector<std::vector<int64_t>> map;

public:
    Model() = default;
    Model(const ModelParams &params);
    Model(const Model &other);

    ~Model() = default;

    std::vector<std::vector<int64_t>> &start();
    void step();
};
