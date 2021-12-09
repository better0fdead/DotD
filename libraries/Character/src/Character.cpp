#include "Character.hpp"

void Character::takeDamage() {
    HPcurrent--;
}

bool Character::isDead() {
    return HPcurrent <= 0;
}
