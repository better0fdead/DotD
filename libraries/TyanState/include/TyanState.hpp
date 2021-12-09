#pragma once


#include "GameContext.hpp"
#include <memory>
#include "Button.hpp"
#include "client.hpp"
#include "LostState.hpp"
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
    Button f_spell;
    Button s_spell;
    Button th_spell;
    void right_answer();
    void wrong_answer();
    bool answering = false;
    bool answered = false;
    Button back;
    sf::Text question;
    sf::Text win;
    sf::Text lose;
    std::shared_ptr<GameContext> context;  // контекст игры с текстурами и шрифтами, бригаду тоже сюда добавьте
    sf::Sprite pauseBackground;
    sf::Text pauseText; // пример

    int score;
    sf::Text scoreText;
    // todo реализовать класс конпок. здесь добавить кнопки нормальные играть выйти там музыку вырубить
    // todo после нажатия играть переходим в коннектинг стейт и там нашаманьте после конектинга в геймстейт
};