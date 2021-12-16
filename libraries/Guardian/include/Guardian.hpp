#pragma once

#include "Character.hpp"
#include "Bullet.hpp"

#define DELTA_X_FOR_BULLET 45
#define DELTA_Y_FOR_BULLET -40

class Guardian : public Character{
public:
    Guardian(int start_state = 0);

    ~Guardian();

    // а что оставил
    void update(sf::Time deltaTime) override;

    std::vector<Bullet*> shoot(sf::Vector2f direction);

    int checkState();

    void setState(int new_state);

    float viewAngle;
    int GuardianState;
private:
    
};
