#pragma once

#include "Character.hpp"

enum STATES{rateOfFireBuff = 0, bulletSpeedBuff, hpUpBuff, bulletSizeBuff};

class Guardian : public Character {
public:
    Guardian(sf::Vector2f position, sf::Texture *texture);

    ~Guardian();

    void draw(sf::RenderWindow* window);
    void update(double deltaTime);

    void shoot();

private:
    STATES GuardianState;
    float viewAngle;
};
