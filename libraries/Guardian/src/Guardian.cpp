
#include <Guardian.hpp>
#include <iostream>

Guardian::Guardian() : viewAngle(0),  GuardianState(0) {
    HPmax = 1;
    HPcurrent = 1;
}

Guardian::~Guardian() {

}

void Guardian::update(sf::Time deltaTime) {
    if(GuardianState == hpUpBuff){
        HPmax++;
        HPcurrent++;
        GuardianState = 0;
    }
}

std::vector<Bullet*> Guardian::shoot(sf::Vector2f direction) {
    sf::Vector2f bulSpawnPos = {body.getPosition().x + 45, body.getPosition().y - 40};

    std::vector<Bullet*> new_bullets;
    auto bul = new Bullet(bulSpawnPos, direction, GuardianState);
    new_bullets.push_back(bul);

    if(GuardianState == 1) {
        auto bul_mirrored = new Bullet(bulSpawnPos, -direction + 2.f * bulSpawnPos, GuardianState);
        new_bullets.push_back(bul_mirrored);
    }
    return new_bullets;
}

int Guardian::checkState() {
    return GuardianState;
}

void Guardian::setState(int new_state) {
    GuardianState = new_state;
}
