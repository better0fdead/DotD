#pragma once

#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class Character : public Entity {
public:
    Character(): HPmax(1), HPcurrent(1) {};

    virtual ~Character() {};

    virtual void update(sf::Time deltaTime) = 0;


    void takeDamage();

    bool isDead();

protected:
    int HPmax;
    int HPcurrent;
};
