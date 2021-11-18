#pragma once

#include "Character.hpp"

class Tyan : public Character {
public:
    Tyan(sf::Vector2f position, sf::Texture *texture);

    ~Tyan();

    void draw(sf::RenderWindow* window);
    void update(double deltaTime);
    void process_task(int task_num);

private:
    bool isSolvingTask;
};
