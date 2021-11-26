#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.hpp"

class Entity : public sf::Drawable {
public:
    Entity() {};

    virtual ~Entity() {};

    virtual void init(const sf::Texture* texture, sf::Vector2f position) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual void update(double deltaT) = 0;

    //getters
    sf::Vector2f getPos();

    Collider getCollider();

    sf::Vector2f getSize();

    //setters
    void setPos(sf::Vector2f newPos);


protected:
    sf::Sprite body;
    Collider *collider; //Used For Collision Detection
};
