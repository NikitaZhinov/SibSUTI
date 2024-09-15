#include "model.h"

ModelParams::ModelParams() : step_number(0) {}

Model::Model(const ModelParams &params) : params(params) {
    map.resize(params.map_size.y);
    for (std::size_t i = 0; i < params.map_size.y; i++)
        map[i] = std::vector<long long>(params.map_size.x, 0);
}

Model::Model(const Model &other) : params(other.params) {}

std::vector<std::vector<long long>> &Model::start() {
    for (std::size_t i = 0; i < params.step_number; i++)
        step();

    return map;
}

void Model::step() {
    // rabbits
    for (auto rabbit = params.rabbits.begin(); rabbit != params.rabbits.end(); rabbit++) {
        rabbit->move(params.map_size);
        if (rabbit->getAge() % 5 == 0)
            params.rabbits.push_back(Rabbit({ rabbit->getPosition(), rabbit->getDir(), 0, rabbit->getSpeed(), rabbit->getStability() }));
        if (rabbit->getAge() == 10) {
            rabbit = params.rabbits.erase(rabbit);
            if (params.rabbits.size() == 0)
                break;
        }
    }

    // foxes
    params.foxes.sort([](const Fox &a, const Fox &b) {
        if (a.getAge() == b.getAge())
            return a.getAgeMother() < b.getAgeMother();
        return a.getAge() < b.getAge();
    });
    for (auto fox = params.foxes.begin(); fox != params.foxes.end(); fox++) {
        fox->move(params.map_size);
        if (fox->getEated() == 2) {
            fox->reproduction();
            params.foxes.push_back(Fox({ fox->getPosition(), fox->getDir(), 0, fox->getSpeed(), fox->getStability() }));
        }
        if (fox->getAge() == 15) {
            params.foxes.erase(fox);
            if (params.foxes.size() == 0)
                break;
        }
        
        for (auto rabbit = params.rabbits.begin(); rabbit != params.rabbits.end(); rabbit++) {
            if (rabbit->getPosition() == fox->getPosition()) {
                rabbit = params.rabbits.erase(rabbit);
                if (params.rabbits.size() == 0)
                    break;
            }
        }
    }

    // map
    for (std::size_t y = 0; y < params.map_size.y; y++) {
        for (std::size_t x = 0; x < params.map_size.x; x++) {
            map[y][x] = 0;
            long long count = 0;
            for (auto rabbit : params.rabbits)
                if (rabbit.getPosition() == Common::Point(x, y))
                    map[y][x] = ++count;
            count = 0;
            for (auto fox : params.foxes)
                if (fox.getPosition() == Common::Point(x, y))
                    map[y][x] = --count;
        }
    }
}
