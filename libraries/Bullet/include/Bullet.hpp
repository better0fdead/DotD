#pragma once

#include "Entity.hpp"
#include "GameContext.hpp"


#define SPEED_BUFF_COEFF 5

class Bullet : public Entity {
public:
    Bullet(sf::Vector2f position, sf::Vector2f direction, int buffType = 0);
    Bullet(sf::Vector2f position, sf::Texture *texture, int);

    ~Bullet();

//    void setTexture(const sf::Texture* texture);
//    void init(const sf::Texture* texture, sf::Vector2f position) override;
//    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time deltaTime) override;

private:
    sf::Vector2f directionVectNorm;
    float speed;
    float size;
};
