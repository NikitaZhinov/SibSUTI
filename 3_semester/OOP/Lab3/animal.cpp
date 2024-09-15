#include "animal.h"

Animal::Animal() : age_mother(0) {}

Animal::Animal(const AnimalParams &param) : param(param), age_mother(0) {}

void Animal::move(const Common::Point &map_size) {
    switch (param.dir) {
        case 0: {
            if (static_cast<long long>(param.position.y) - static_cast<long long>(param.speed) < 0)
                param.position.y = map_size.y - param.speed;
            else
                param.position.y -= param.speed;
        } break;

        case 1: {
            if (param.position.x + param.speed >= map_size.x)
                param.position.x -= map_size.x - param.speed;
            else
                param.position.x += param.speed;
        } break;

        case 2: {
            if (param.position.y + param.speed >= map_size.y)
                param.position.y -= map_size.y - param.speed;
            else
                param.position.y += param.speed;
        } break;

        case 3: {
            if (static_cast<long long>(param.position.x) - static_cast<long long>(param.speed) < 0)
                param.position.x = map_size.x - param.speed;
            else
                param.position.x -= param.speed;
        } break;

        default:
            break;
    }
    aging();
    if (param.age % param.stability == 0)
        turn();
}

void Animal::aging() {
    param.age++;
    age_mother++;
}

void Animal::turn() {
    param.dir = (param.dir == 3) ? 0 : param.dir + 1;
}

Common::Point Animal::getPosition() {
    return param.position;
}

std::size_t Animal::getAge() const {
    return param.age;
}

std::size_t Animal::getDir() {
    return param.dir;
}

std::size_t Animal::getStability() {
    return param.stability;
}

std::size_t Animal::getSpeed() {
    return param.speed;
}

std::size_t Animal::getAgeMother() const {
    return age_mother;
}

Fox::Fox() : eated(0) {}

Rabbit::Rabbit(const AnimalParams &param) {
    this->param = param;
}

Fox::Fox(const AnimalParams &param) : Fox::Fox() {
    this->param = param;
}

void Fox::eating() {
    eated++;
}

void Fox::reproduction() {
    eated = 0;
}

std::size_t Fox::getEated() {
    return eated;
}
