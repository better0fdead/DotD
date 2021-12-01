#pragma once

#include "State.hpp"
#include "StateManager.hpp"
#include "GameContext.hpp"
#include <memory>

#include <SFML/Graphics/Text.hpp>

class PauseState : public State {
public:
    PauseState(std::shared_ptr<GameContext>& context);

    ~PauseState();

    void init() override;
    void processStuff() override;
    void update(sf::Time deltaT) override;
    void draw() override;

private:
    std::shared_ptr<GameContext> context;  // контекст игры с текстурами и шрифтами, бригаду тоже сюда добавьте
    sf::Sprite pauseBackground;
    sf::Text pauseText; // пример
    // todo реализовать класс конпок. здесь добавить кнопки нормальные играть выйти там музыку вырубить
    // todo после нажатия играть переходим в коннектинг стейт и там нашаманьте после конектинга в геймстейт
};