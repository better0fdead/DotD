#include "Collider.hpp"
#include <cmath>
#include <iostream>


Collider::Collider(sf::Sprite* body)
        :body(body)
{
}


Collider::~Collider()
{
}


bool Collider::checkCollision(const Collider& other)
{
   // расстояние между центрами
    sf::Vector2f delta(this->getPos() - other.getPos());

    sf::Vector2f halfSize(this->getHalfSize() + other.getHalfSize());


    if (std::abs(delta.x) - halfSize.x < 0 && std::abs(delta.y) - halfSize.y < 0)
    {
        return true;
    }


    return false;
}


sf::Vector2f Collider::getHalfSize() const
{
//    std::cout << body->getGlobalBounds().top * body->getScale().x << " " << body->getGlobalBounds().left * body->getScale().y << std::endl;
    return sf::Vector2f(body->getGlobalBounds().width * body->getScale().x / 2.0f, body->getGlobalBounds().height * body->getScale().y / 2.0f);
}


sf::Vector2f Collider::getPos() const
{
    return sf::Vector2f(body->getPosition());
}