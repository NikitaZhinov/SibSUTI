#pragma once

#include "common.h"

struct AnimalParams {
    Common::Point position;
    std::size_t dir = 0;
    std::size_t age = 0;
    std::size_t speed = 0;
    std::size_t stability = 0;
};

class Animal {
protected:
    AnimalParams param;
    std::size_t age_mother;

public:
    Animal();
    Animal(const AnimalParams &param);

    void move(const Common::Point &map_size);
    void aging();
    void turn();

    Common::Point getPosition();
    std::size_t getAge() const;
    std::size_t getDir();
    std::size_t getStability();
    std::size_t getSpeed();
    std::size_t getAgeMother() const;
};

class Rabbit : public Animal {
public:
    Rabbit(const AnimalParams &param);
};

class Fox : public Animal {
    std::size_t eated;

public:
    Fox();
    Fox(const AnimalParams &param);

    void eating();
    void reproduction();

    std::size_t getEated();
};
