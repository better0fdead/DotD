#pragma once

#include "Character.hpp"

class Tyan : public Character {
public:
    Tyan();

    ~Tyan();

    // пока хз надо ли это, оставил
    void update(sf::Time deltaTime) override;

    // write smth here
    //

private:
    bool isSolvingTask;
};
