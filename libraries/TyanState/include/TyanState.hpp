#pragma once


#include "GameContext.hpp"
#include <memory>
#include "Button.hpp"

#include <SFML/Graphics/Text.hpp>

class TyanState : public State {
public:
    TyanState(std::shared_ptr<GameContext>& context);

    ~TyanState();

    void init() override;
    void updateKeyBinds() override;
    void processStuff() override;
    void update(sf::Time deltaT) override;
    void draw() override;
    void task();

    void resume();

private:
    Button f_answer;
    Button s_answer;
    Button t_answer;
    void right_answer();
    void wrong_answer();
    bool answered = false;
    sf::Text question;
    sf::Text win;
    sf::Text lose;
    std::shared_ptr<GameContext> context;  // контекст игры с текстурами и шрифтами, бригаду тоже сюда добавьте
    sf::Sprite pauseBackground;
    sf::Text pauseText; // пример
    // todo реализовать класс конпок. здесь добавить кнопки нормальные играть выйти там музыку вырубить
    // todo после нажатия играть переходим в коннектинг стейт и там нашаманьте после конектинга в геймстейт
};