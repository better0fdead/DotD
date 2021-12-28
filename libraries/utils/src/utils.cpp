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

    SIDE side = (SIDE)(rand() % 4);
    switch (side) {
        case SIDE::top:
            position.x = get_random(0, WINDOW_WIDTH);
            position.y = -BORDER_MARGIN;
            break;
        case SIDE::bottom:
            position.x = get_random(0, WINDOW_WIDTH);
            position.y = WINDOW_HEIGHT + BORDER_MARGIN;
            break;
        case SIDE::left:
            position.x = -BORDER_MARGIN;
            position.y = get_random(0, WINDOW_HEIGHT);
            break;
        case SIDE::right:
            position.x = WINDOW_WIDTH + BORDER_MARGIN;
            position.y = get_random(0, WINDOW_HEIGHT);
            break;
    }
    return position;
}

sf::Vector2f get_rand_pos_in_centre() {
    return sf::Vector2f(get_random(WINDOW_WIDTH / 2 - CENTRE_INTERVAL, WINDOW_WIDTH / 2 + CENTRE_INTERVAL),
                        get_random(WINDOW_HEIGHT / 2 - CENTRE_INTERVAL, WINDOW_HEIGHT / 2 + CENTRE_INTERVAL));
}
