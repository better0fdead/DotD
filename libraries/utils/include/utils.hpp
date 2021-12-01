#pragma once

#include <cassert>
#include <cmath>
#include <SFML/System.hpp>
#include "GameContext.hpp"

#define CENTRE_INTERVAL 50

enum SIDE {top = 0, bottom, left, right};

float get_random(float left_limit, float right_limit);  // рандомный флоат

sf::Vector2f get_rand_pos_around_frame();  // рандомная позиция вокруг рамки

sf::Vector2f get_rand_pos_in_centre();  // рандомная позиция около центра
