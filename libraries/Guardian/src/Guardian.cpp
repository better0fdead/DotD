#include <Guardian.hpp>
#include <iostream>

Guardian::Guardian(STATES start_state) : GuardianState(start_state) {
    HPmax = 1;
    HPcurrent = 1;
    if (start_state == STATES::hpUpBuff) {
        HPcurrent++;
        HPmax++;
    }
}

Guardian::~Guardian() {

}

void Guardian::update(sf::Time deltaTime) {
    if (GuardianState == STATES::hpUpBuff) {
        HPmax++;
        HPcurrent++;
        GuardianState = STATES::normal;
    }
}

std::vector<Bullet *> Guardian::shoot(sf::Vector2f direction) {
    sf::Vector2f bulSpawnPos = {body.getPosition().x + DELTA_X_FOR_BULLET, body.getPosition().y + DELTA_Y_FOR_BULLET};

    std::vector<Bullet *> new_bullets;
    auto bul = new Bullet(bulSpawnPos, direction, GuardianState);
    new_bullets.push_back(bul);

    if (GuardianState == STATES::fireBackwardsBuff) {
        auto bul_mirrored = new Bullet(bulSpawnPos, -direction + 2.f * bulSpawnPos, GuardianState);
        new_bullets.push_back(bul_mirrored);
    }
    return new_bullets;
}

STATES Guardian::checkState() const {
    return GuardianState;
}

void Guardian::setState(STATES new_state) {
    GuardianState = new_state;
}
