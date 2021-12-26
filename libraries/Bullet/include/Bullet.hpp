#pragma once

#include <valarray>
#include "Entity.hpp"
#include "GameContext.hpp"

constexpr uint8_t SPEED_BUFF_COEFF = 5;
constexpr uint8_t DEFAULT_SPEED = 7;
constexpr uint8_t DEFAULT_SIZE = 1;

class Bullet : public Entity {
public:
    Bullet(sf::Vector2f position, sf::Vector2f direction, STATES buffType = STATES::normal);
    Bullet(float xPos, float yPos, float rotationDegree, float size = 1);

    ~Bullet();
    float direction_x;
    float direction_y;

    void update(sf::Time deltaTime) override;

private:
    sf::Vector2f directionVectNorm;
    float speed;
    float size;
};
