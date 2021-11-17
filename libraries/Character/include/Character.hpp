#pragma once

#include "Entity.hpp"

class Character : public Entity {
public:
    Character(sf::Vector2f position, sf::Texture *texture);

    ~Character();

    virtual void draw(sf::RenderWindow window) = 0;
    virtual void update(double deltaTime) = 0;


    void takeDamage();
    bool isDead()

private:
    int HPmax;
    int HPcurrent;
};
