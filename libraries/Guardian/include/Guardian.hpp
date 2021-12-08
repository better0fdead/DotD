#pragma once

#include "Character.hpp"
#include "Bullet.hpp"


class Guardian : public Character{
public:
    Guardian();

    ~Guardian();

    // а что оставил
    void update(sf::Time deltaTime) override;

    std::vector<Bullet*> shoot(sf::Vector2f direction);

    int checkState();

    void setState(int new_state);

    float viewAngle;
private:
    int GuardianState;
};
