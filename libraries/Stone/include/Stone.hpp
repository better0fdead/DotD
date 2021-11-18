#pragma once

#include "Entity.hpp"

class Stone : public Entity {
public:
    Stone(sf::Vector2f position, sf::Texture *texture);

    ~Stone();

    void draw(sf::RenderWindow* window);
    void update(double deltaTime);

    void StoneSpawner();

private:
    float speed;
    sf::Vector2f direction;
    sf::Vector2f spawnLocation;
    float size;
};
