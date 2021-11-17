#pragma once

#include "Character.hpp"

class Tyan : public Character {
public:
    Tyan(sf::Vector2f position, sf::Texture *texture);

    ~Tyan();

    void draw(sf::RenderWindow window);
    void update(double deltaTime);

    // write smth here
    //

private:
    bool isSolvingTask;
};
