#pragma once

#include "Entity.hpp"

class Bullet : public Entity {
public:
    Bullet(sf::Vector2f position, sf::Texture *texture);
    Bullet(sf::Vector2f position, sf::Texture *texture, int);

    ~Bullet();

    void draw(sf::RenderWindow window);
    void update(double deltaTime);

private:
    float speed;
    float size;
};
