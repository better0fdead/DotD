#pragma once

#include "Entity.hpp"
#include "utils.hpp"

#define SIZE_SCALE_MIN 1
#define SIZE_SCALE_MAX 1.5

class Stone : public Entity {
public:
    Stone(float speed);

    ~Stone();

    void setDirection();  // инициализирует вектор нормали движения
    void update(sf::Time deltaTime) override;

private:
    float speed;
    float rotationSpeed;
    sf::Vector2f directionVectNorm;
    float size;
};
