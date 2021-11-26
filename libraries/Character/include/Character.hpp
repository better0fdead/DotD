#pragma once

#include "Entity.hpp"
#include <SFML/Graphics.hpp>

class Character : public Entity {
public:
    Character() {};

    virtual ~Character() {};

    // присваиваем текстурку и ставим на место персонажа нашего
    void init(const sf::Texture* texture, sf::Vector2f position) override;
    //рисуем, это метод наследуемый от дровабл, там почитайте че за таргет и стейтс
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void update(double deltaTime) = 0;


    void takeDamage();
    bool isDead();

protected:
    int HPmax;
    int HPcurrent;
};
