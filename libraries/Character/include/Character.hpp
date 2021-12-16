#pragma once

#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class Character : public Entity {
public:

    virtual ~Character() {};

    virtual void update(sf::Time deltaTime) = 0;


    void takeDamage();

    bool isDead();

protected:
    int HPmax;
    int HPcurrent;
};
