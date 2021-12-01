
#include <Guardian.hpp>
#include <iostream>

Guardian::Guardian() : viewAngle(0),  GuardianState(0) {
//    collider = new Collider(&body);
    HPmax = 1;
    HPcurrent = 1;
}

Guardian::~Guardian() {

}

void Guardian::update(sf::Time deltaTime) {
//    viewAngle = (float)sf::Mouse::getPosition().x;
//    std::cout << viewAngle << std::endl;
//collider->checkCollision()
}

Bullet* Guardian::shoot(sf::Vector2f direction) {
    auto bul = new Bullet({body.getPosition().x + 45, body.getPosition().y - 40}, direction);
//    bul->setPos({body.getPosition().x + 25, body.getPosition().y - 50});
//    std::cout << bul->getPos().x << bul->getPos().y;
    return bul;
}
