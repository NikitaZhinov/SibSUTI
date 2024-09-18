#pragma once

#include "point.h"

struct AnimalParams {
    Point position;
    std::size_t dir = 0;
    std::size_t stability = 0;
};

class Animal {
protected:
    AnimalParams param;
    std::size_t age;
    std::size_t speed;

public:
    Animal();
    Animal(const AnimalParams &param);

    ~Animal() = default;

    void move(const Point &map_size);
    virtual void aging() = 0;
    void turn();

    Point getPosition();
    std::size_t getAge() const;
    std::size_t getDir();
    std::size_t getStability();
    std::size_t getSpeed();
};

class Rabbit : public Animal {
public:
    Rabbit();
    Rabbit(const AnimalParams &param);

    ~Rabbit() = default;

    void aging() override;
};

class Fox : public Animal {
    std::size_t eated;
    std::size_t age_mother;

public:
    Fox();
    Fox(const AnimalParams &param, std::size_t age_mother);

    ~Fox() = default;

    void eating();
    void reproduction();

    void aging() override;

    std::size_t getEated();
    std::size_t getAgeMother() const;
};
