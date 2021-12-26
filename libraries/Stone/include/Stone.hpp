#pragma once

#include "Entity.hpp"
#include "utils.hpp"

constexpr float SIZE_SCALE_MIN = 0.5;
constexpr uint8_t SIZE_SCALE_MAX = 1;

class Stone : public Entity {
public:
    Stone(float speed);
    Stone(float xPos, float yPos, float rotationDegree, float size = 1);

    ~Stone();

    void setDirection();  // инициализирует вектор нормали движения
    void update(sf::Time deltaTime) override;

private:
    sf::Vector2f directionVectNorm;
    float speed;
    float rotationSpeed;
    float size;
};
