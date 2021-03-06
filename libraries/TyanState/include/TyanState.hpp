#pragma once


#include "GameContext.hpp"
#include <memory>
#include "Button.hpp"
#include "client.hpp"
#include "Tyan.hpp"
#include "Guardian.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "LostState.hpp"
#include <SFML/Graphics/Text.hpp>
#include "tasks.hpp"

class TyanState : public State , public Tasks,public Client {
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

    void init_question();
    void init_win();
    void init_main();

    void colide_question(sf::Event event);
    void colide_menu(sf::Event event);

    void right_answer();
    void wrong_answer();

    bool answering = false;
    bool answered = false;
    bool gaming = false;

    sf::Sprite background;

    std::unique_ptr<Guardian> guardian;

    std::unique_ptr<Tyan> tyan;

    int timer;
    int timer_2;
    int buff = 0;
    Button back;
    sf::Text question;
    sf::Text timeQuestion;
    sf::Text choose_str;
    sf::Text win;
    sf::Text lose;
    std::vector<Bullet*> bulletsVec;
    std::vector<Stone *> stonesVec;
    std::shared_ptr<GameContext> context;  // контекст игры с текстурами и шрифтами, бригаду тоже сюда добавьте
    sf::Sprite pauseBackground;
    sf::Text pauseText; // пример
    Client player_tyan;
    int score;
    sf::Text scoreText;
    // todo реализовать класс конпок. здесь добавить кнопки нормальные играть выйти там музыку вырубить
    // todo после нажатия играть переходим в коннектинг стейт и там нашаманьте после конектинга в геймстейт
};