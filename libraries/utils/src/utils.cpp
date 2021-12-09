#include "utils.hpp"
#include <iostream>

float get_random(float left_limit, float right_limit) {
    assert(right_limit > left_limit);
    float random = ((float) rand()) / (float) RAND_MAX;

    float range = right_limit - left_limit;
    return (random * range) + left_limit;
}

sf::Vector2f get_rand_pos_around_frame() {
    sf::Vector2f position = {0, 0};

    srand(time(nullptr));
    int side = rand() % 4;
    switch (side) {
        case top:
            position.x = get_random(0, WINDOW_WIDTH);
            position.y = -200;
            break;
        case bottom:
            position.x = get_random(0, WINDOW_WIDTH);
            position.y = WINDOW_HEIGHT + 200;
            break;
        case left:
            position.x = -200;
            position.y = get_random(0, WINDOW_HEIGHT);
            break;
        case right:
            position.x = WINDOW_WIDTH + 200;
            position.y = get_random(0, WINDOW_HEIGHT);
            break;
    }
    return position;
}

sf::Vector2f get_rand_pos_in_centre() {
    return sf::Vector2f(get_random(WINDOW_WIDTH / 2 - CENTRE_INTERVAL, WINDOW_WIDTH / 2 + CENTRE_INTERVAL),
                        get_random(WINDOW_HEIGHT / 2 - CENTRE_INTERVAL, WINDOW_HEIGHT / 2 + CENTRE_INTERVAL));
}
