#pragma once

#include "Entity.hpp"

class Button : public Entity {
public:
    Button();
    ~Button();

    void update(sf::Time deltaTime) override;

private:
    //write smth
};
