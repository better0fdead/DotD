#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.hpp"

class Entity : public sf::Drawable {
public:
    Entity() {};

    virtual ~Entity() {};

    // присваиваем текстурку и ставим на место персонажа нашего
    void init(const sf::Texture *texture, sf::Vector2f position);

    //рисуем, это метод наследуемый от дровабл, там почитайте че за таргет и стейтс
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    virtual void update(sf::Time deltaT) = 0;

    //getters
    sf::Vector2f getPos() const;

    Collider getCollider();

    //setters
    void setPos(sf::Vector2f newPos);


protected:
    sf::Sprite body;
    Collider *collider; //Used For Collision Detection
};
