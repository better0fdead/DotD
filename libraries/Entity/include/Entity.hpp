#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.hpp"

class Entity {
public:
    Entity(sf::Vector2f position, sf::Texture *texture);

    ~Entity();

    virtual void draw(sf::RenderWindow *w) = 0; //Drawing function for Entity
    virtual void update(double deltaT) = 0;  //Update Function for Entity

    //getters
    sf::Vector2f getPos();

    Collider getCollider();

    sf::RectangleShape getBody();

    sf::Vector2f getSize();

    //setters
    void setPos(sf::Vector2f newPos);

//    void setSize(sf::Vector2f newSize);

private:
    sf::RectangleShape body; //The Body of the Entity
    sf::Texture texture;
    Collider *collider; //Used For Collision Detection
};
