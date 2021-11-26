#pragma once
#include "State.hpp"
#include "GameContext.hpp"
#include "StateManager.hpp"
#include <memory>

#include <SFML/Graphics/Text.hpp>

class MenuState : public State {
public:
    MenuState(std::shared_ptr<GameContext>& context);

    ~MenuState();

    void init() override;
    void processStuff() override;
    void update(sf::Time deltaT) override;
    void draw() override;

private:
std::shared_ptr<GameContext> context;  // контекст игры с текстурами и шрифтами, бригаду тоже сюда добавьте
sf::Text playText; // пример
 // todo реализовать класс конпок. здесь добавить кнопки нормальные играть выйти там музыку вырубить
 // todo после нажатия играть переходим в коннектинг стейт и там нашаманьте после конектинга в геймстейт
};