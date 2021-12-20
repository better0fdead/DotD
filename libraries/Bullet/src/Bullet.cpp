#include "Bullet.hpp"

Bullet::Bullet(sf::Vector2f position, sf::Vector2f direction, STATES buffType) : speed(DEFAULT_SPEED), size(DEFAULT_SIZE) {
    body.setPosition(position);

    switch (buffType) {
        case STATES::normal: {
            break;
        }
        case STATES::bulletSpeedBuff: {
            speed *= SPEED_BUFF_COEFF;
            break;
        }
        case STATES::bulletSizeBuff: {
            size *= 2;
            break;
        }
    }

    body.scale(size, size);
    // ищем нормированный вектор направления полета пули
    auto directionVect = direction - position;
    directionVectNorm = directionVect / (float) sqrt(directionVect.x * directionVect.x +
                                                     directionVect.y * directionVect.y);

    // вращаем текстурку
    body.setRotation((float) (atan2f(directionVectNorm.x, directionVectNorm.y) * (-180.0f / 3.14159265f)) + 90);
}

Bullet::~Bullet() {

}

void Bullet::update(sf::Time deltaTime) {
    auto curPos = body.getPosition();
    body.setPosition((curPos + (directionVectNorm * speed)));
}
