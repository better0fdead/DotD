#include "Character.hpp"

void Character::init(const sf::Texture *texture, sf::Vector2f position) {
    body.setTexture(*texture);  // присваем текстурку
    body.setOrigin(body.getLocalBounds().width / 2,
                   body.getLocalBounds().height / 2);  // ставим начальную точку в центр

    body.setPosition(position);  // позиционируем
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(body);  // рисуем :)
}