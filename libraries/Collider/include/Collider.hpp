#pragma once

#include <SFML/Graphics.hpp>

class Collider
{
public:
    Collider(sf::RectangleShape* body);

    ~Collider();

    bool checkCollision(const Collider & other);


    //getters
    sf::Vector2f getHalfSize() const;  // for AABB collision detection
    sf::Vector2f getPos() const;

private:
    sf::RectangleShape* body;
};
