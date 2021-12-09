#pragma once

#include <SFML/Graphics.hpp>

class Collider
{
public:
    Collider(sf::Sprite* body);

    ~Collider();

    bool checkCollision(const Collider & other);


    sf::Vector2f getPos() const;

private:
    sf::Sprite* body;
};
