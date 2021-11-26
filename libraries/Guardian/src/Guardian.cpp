
#include <Guardian.hpp>

Guardian::Guardian() : GuardianState(0), viewAngle(0) {
    HPmax = 1;
    HPcurrent = 1;
}

Guardian::~Guardian() {

}

void Guardian::update(double deltaTime) {
}
