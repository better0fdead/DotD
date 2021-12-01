#include <iostream>
#include "Stone.hpp"

Stone::Stone(float speed) : speed(speed) {
//    collider = new Collider(&body);

    size = get_random(SIZE_SCALE_MIN, SIZE_SCALE_MAX);
    body.scale(sf::Vector2f(size, size));  // задаем рандомный размер камню

    // задаем скорость вращения
    bool clockwise = rand() % 2 - 1;
    if (clockwise) {
        rotationSpeed = get_random(1, 7);
    } else {
        rotationSpeed = -get_random(1, 7);
    }
}

Stone::~Stone() {

}

void Stone::update(sf::Time deltaTime) {
    ////позиционирование, когда камень уходит за границу////
    if (body.getPosition().x < (float) (-body.getLocalBounds().left - body.getLocalBounds().width / 2)) {
        body.setPosition(sf::Vector2f((WINDOW_WIDTH + body.getLocalBounds().width / 2), body.getPosition().y));
    }
    if (body.getPosition().x > (float) (WINDOW_WIDTH + body.getLocalBounds().width / 2)) {
        body.setPosition(
                sf::Vector2f((-body.getLocalBounds().width / 2), body.getPosition().y));
    }
    if (body.getPosition().y > (float) (WINDOW_HEIGHT + body.getLocalBounds().height / 2)) {
        body.setPosition(sf::Vector2f(body.getPosition().x, (-body.getLocalBounds().height / 2)));
    }
    if (body.getPosition().y < (float) (-body.getLocalBounds().top - body.getLocalBounds().height / 2)) {
        body.setPosition(sf::Vector2f(body.getPosition().x, (WINDOW_HEIGHT + body.getLocalBounds().height / 2)));
    }
    ////////////////////////////////////////////////////////

    // движение каджый кадр
    body.setPosition((body.getPosition() + (directionVectNorm * speed)));

    // вращение каждый кадр
    body.rotate(rotationSpeed);
}

void Stone::setDirection() {
    // получаем нормированный вектор направления движения (почти всегда направлен в сторону центра)
    auto direction =  body.getPosition() - get_rand_pos_in_centre();
    directionVectNorm = direction / (float) sqrt(pow(direction.x, 2) + pow(direction.y, 2));
}
