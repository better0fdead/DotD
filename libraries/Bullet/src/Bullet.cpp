#include <valarray>
#include <iostream>
#include "Bullet.hpp"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction, int buffType) : speed(DEFAULT_SPEED), size(1) {
    body.setPosition(position);

    switch (buffType) {
        case normal:
        {
            break;
        }
        case bulletSpeedBuff:
        {
        speed *= SPEED_BUFF_COEFF;
        break;
        }
        case bulletSizeBuff:
        {
            size *= 2;
            break;
        }
    }

    body.scale(size,size);
    // ищем нормированный вектор направления полета пули
    auto directionVect = direction - position;
    directionVectNorm = directionVect / (float) sqrt(pow(directionVect.x, 2) + pow(directionVect.y, 2));

    // вращаем текстурку
    body.setRotation((float) (atan2f(directionVectNorm.x, directionVectNorm.y) * (-180.0f / 3.14159265f)) + 90);
}

Bullet::Bullet(sf::Vector2f position, sf::Texture *texture, int) {

}

Bullet::~Bullet() {

}

void Bullet::update(sf::Time deltaTime) {
    auto curPos = body.getPosition();
    body.setPosition((curPos + (directionVectNorm * speed)));
}

