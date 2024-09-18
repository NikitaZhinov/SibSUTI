#include "animal.h"

#include <cstdint>

Animal::Animal() : age(0), speed(0) {}

Animal::Animal(const AnimalParams &param) : param(param), age(0), speed(0) {}

void Animal::move(const Point &map_size) {
    switch (param.dir) {
        case 0: {
            if (static_cast<int64_t>(param.position.y) - static_cast<int64_t>(speed) < 0)
                param.position.y = map_size.y + param.position.y - speed;
            else
                param.position.y -= speed;
        } break;

        case 1: {
            if (param.position.x + speed >= map_size.x)
                param.position.x -= map_size.x - speed;
            else
                param.position.x += speed;
        } break;

        case 2: {
            if (param.position.y + speed >= map_size.y)
                param.position.y -= map_size.y - speed;
            else
                param.position.y += speed;
        } break;

        case 3: {
            if (static_cast<int64_t>(param.position.x) - static_cast<int64_t>(speed) < 0)
                param.position.x = map_size.x + param.position.x - speed;
            else
                param.position.x -= speed;
        } break;

        default:
            break;
    }
    aging();
    turn();
}

void Animal::turn() {
    if (age % param.stability == 0)
        param.dir = (param.dir + 1) % 4;
}

Point Animal::getPosition() {
    return param.position;
}

std::size_t Animal::getAge() const {
    return age;
}

std::size_t Animal::getDir() {
    return param.dir;
}

std::size_t Animal::getStability() {
    return param.stability;
}

std::size_t Animal::getSpeed() {
    return speed;
}

Rabbit::Rabbit() {
    speed = 1;
    age = 0;
}

Rabbit::Rabbit(const AnimalParams &param) : Rabbit::Rabbit() {
    this->param = param;
}

void Rabbit::aging() {
    age++;
}

Fox::Fox() : eated(0), age_mother(0) {
    speed = 2;
    age = 0;
}

Fox::Fox(const AnimalParams &param, std::size_t age_mother) : Fox::Fox() {
    this->param = param;
    this->age_mother = age_mother;
}

void Fox::eating() {
    eated++;
}

void Fox::reproduction() {
    eated -= 2;
}

void Fox::aging() {
    age++;
    age_mother++;
}

std::size_t Fox::getEated() {
    return eated;
}

std::size_t Fox::getAgeMother() const {
    return age_mother;
}
