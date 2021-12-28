#include "Entity.hpp"

void Entity::init(const sf::Texture *texture, sf::Vector2f position) {
    collider = new Collider(&body);

    body.setTexture(*texture);  // присваем текстурку
    body.setOrigin(body.getLocalBounds().width / 2,
                   body.getLocalBounds().height / 2);  // ставим начальную точку в центр
    body.setPosition(position);  // позиционируем
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(body);  // рисуем :)
}

sf::Vector2f Entity::getPos() const {
    return body.getPosition();
}

void Entity::setPos(sf::Vector2f newPos) {
    body.setPosition(newPos);
}

Collider Entity::getCollider() {
    return *collider;
}
