#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.hpp"

constexpr uint8_t DEFAULT_MAX_HP = 1;

class Character : public Entity {
public:
    Character(): HPmax(DEFAULT_MAX_HP), HPcurrent(DEFAULT_MAX_HP) {};

    virtual ~Character() {};

    virtual void update(sf::Time deltaTime) = 0;

    void takeDamage();

    bool isDead();

protected:
    int HPmax;
    int HPcurrent;
};
