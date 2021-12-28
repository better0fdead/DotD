#pragma once

#include <SFML/Graphics.hpp>

constexpr float FIRST_COLLIDER_COEFF = 0.9;

constexpr float SECOND_COLLIDER_COEFF = 0.8;

class Collider {
public:
    Collider(sf::Sprite *body);

    ~Collider();

    bool checkCollision(const Collider &other);

    sf::Vector2f getPos() const;

private:
    sf::Sprite *body;
};
