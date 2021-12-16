#pragma once

#include "Character.hpp"
#include "Bullet.hpp"

constexpr int8_t DELTA_X_FOR_BULLET = 45;
constexpr int8_t DELTA_Y_FOR_BULLET =  -40;

class Guardian : public Character {
public:
    Guardian(STATES start_state = STATES::normal);

    ~Guardian();

    void update(sf::Time deltaTime) override;

    std::vector<Bullet *> shoot(sf::Vector2f direction);

    STATES checkState() const;

    void setState(STATES new_state);

private:
    STATES GuardianState;
};
