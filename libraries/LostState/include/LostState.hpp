#pragma once

#include <memory>
#include "MenuState.hpp"

class LostState : public State {
public:
    LostState(std::shared_ptr<GameContext> &context, int totalScore);

    ~LostState();

    void init() override;
    void updateKeyBinds() override;
    void processStuff() override;
    void update(sf::Time deltaT) override;
    void draw() override;

private:
    std::shared_ptr<GameContext> context;  // контекст игры с текстурами и шрифтами, бригаду тоже сюда добавьте

    int score;
    sf::Text scoreText;

    sf::Sprite lostBackground;
    sf::Text lostText;

    // todo реализовать класс конпок. здесь добавить кнопки нормальные играть заново выйти в меню
};
