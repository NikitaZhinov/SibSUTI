#include "model.h"

ModelParams::ModelParams() : step_number(0) {}

Model::Model(const ModelParams &params) : params(params) {
    map.resize(params.map_size.y);
    for (std::size_t i = 0; i < params.map_size.y; i++)
        map[i] = std::vector<int64_t>(params.map_size.x, 0);
}

Model::Model(const Model &other) : params(other.params) {}

std::vector<std::vector<int64_t>> &Model::start() {
    for (std::size_t i = 0; i < params.step_number; i++)
        step();

    return map;
}

void Model::step() {
    // rabbits
    std::vector<std::list<Rabbit>::iterator> new_rabbits;
    std::vector<std::list<Rabbit>::iterator> old_rabbits;
    for (auto rabbit = params.rabbits.begin(); rabbit != params.rabbits.end(); rabbit++) {
        rabbit->move(params.map_size);
        if (rabbit->getAge() % 5 == 0)
            new_rabbits.push_back(rabbit);
        if (rabbit->getAge() == 10)
            old_rabbits.push_back(rabbit);
    }
    for (auto old_rabbit : old_rabbits)
        params.rabbits.erase(old_rabbit);
    for (auto new_rabbit : new_rabbits)
        params.rabbits.push_back(Rabbit({ new_rabbit->getPosition(), new_rabbit->getDir(), new_rabbit->getStability() }));

    // foxes
    std::vector<std::list<Fox>::iterator> new_foxes;
    std::vector<std::list<Fox>::iterator> old_foxes;
    std::vector<std::list<Rabbit>::iterator> eated_rabbits;
    params.foxes.sort([](const Fox &a, const Fox &b) {
        if (a.getAge() == b.getAge())
            return a.getAgeMother() > b.getAgeMother();
        return a.getAge() > b.getAge();
    });
    for (auto fox = params.foxes.begin(); fox != params.foxes.end(); fox++) {
        fox->move(params.map_size);
        
        if (fox->getAge() == 15)
            old_foxes.push_back(fox);
        
        for (auto rabbit = params.rabbits.begin(); rabbit != params.rabbits.end(); rabbit++) {
            if (rabbit->getPosition() == fox->getPosition()) {
                eated_rabbits.push_back(rabbit);
                fox->eating();
            }
        }

        if (fox->getEated() >= 2) {
            fox->reproduction();
            new_foxes.push_back(fox);
        }
    }
    for (auto old_fox : old_foxes)
        params.foxes.erase(old_fox);
    for (auto new_fox : new_foxes)
        params.foxes.push_back(Fox({ new_fox->getPosition(), new_fox->getDir(), new_fox->getStability() }, new_fox->getAge()));
    for (auto eated_rabbit : eated_rabbits)
        params.rabbits.erase(eated_rabbit);

    // map
    for (std::size_t y = 0; y < params.map_size.y; y++) {
        for (std::size_t x = 0; x < params.map_size.x; x++) {
            map[y][x] = 0;
            long long count = 0;
            for (auto rabbit : params.rabbits)
                if (rabbit.getPosition() == Point(x, y))
                    map[y][x] = ++count;
            count = 0;
            for (auto fox : params.foxes)
                if (fox.getPosition() == Point(x, y))
                    map[y][x] = --count;
        }
    }
}
