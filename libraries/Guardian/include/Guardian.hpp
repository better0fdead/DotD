#pragma once

#include "Character.hpp"

enum STATES{normal = 0, rateOfFireBuff, bulletSpeedBuff, hpUpBuff, bulletSizeBuff};

class Guardian : public Character{
public:
    Guardian();

    ~Guardian();

    // а что оставил
    void update(double deltaTime) override;

    void shoot();

private:
    int GuardianState;
    float viewAngle;
};
