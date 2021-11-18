#pragma once

#include "Entity.hpp"

class Button : public Entity {
public:
    Button(sf::Vector2f position, sf::Texture *texture);
    ~Button();

    void draw(sf::RenderWindow* window);
    void update(double deltaTime);

private:
    //write smth
};
