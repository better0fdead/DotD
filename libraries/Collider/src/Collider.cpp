#include "Collider.hpp"
#include <cmath>
#include <iostream>


Collider::Collider(sf::Sprite *body) : body(body) {
}


Collider::~Collider() {
}


bool Collider::checkCollision(const Collider &other) {

    // расстояние между центрами
    sf::Vector2f delta(this->getPos() - other.getPos());

    auto dist = sqrt(delta.x * delta.x + delta.y * delta.y);

    auto radius1 = std::min(body->getGlobalBounds().width,
                            body->getGlobalBounds().height) / 2;

    auto radius2 = std::min(other.body->getGlobalBounds().width,
                            other.body->getGlobalBounds().height) / 2;

    if (dist < radius1 * FIRST_COLLIDER_COEFF + radius2 * SECOND_COLLIDER_COEFF) {
        return true;
    }
    return false;
}

sf::Vector2f Collider::getPos() const {
    return sf::Vector2f(body->getPosition());
}
