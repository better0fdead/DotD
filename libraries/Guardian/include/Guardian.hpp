#pragma once

#include "Character.hpp"
#include "Bullet.hpp"

enum STATES{normal = 0, rateOfFireBuff, bulletSpeedBuff, hpUpBuff, bulletSizeBuff};

class Guardian : public Character{
public:
    Guardian();

    ~Guardian();

    // а что оставил
    void update(sf::Time deltaTime) override;

    Bullet shoot(sf::Vector2f direction);

    float viewAngle;
private:
    int GuardianState;
};
