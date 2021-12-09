#pragma once


//#include "State.hpp"
//#include "StateManager.hpp"
//#include "GameContext.hpp"
#include "MenuState.hpp"
//#include "GameState.hpp"
#include <memory>

class LostState : public State {
public:
    LostState(std::shared_ptr<GameContext> &context, int totalScore);

    ~LostState();

    void init() override;
    void updateKeyBinds() override;
    void processStuff() override;
    void update(sf::Time deltaT) override;
    void draw() override;


//    bool switchState() override; //Play again?

//    void setScore(std::string newScore); //Displays the score

private:
    std::shared_ptr<GameContext> context;  // контекст игры с текстурами и шрифтами, бригаду тоже сюда добавьте

    int score;
    sf::Text scoreText;

    sf::Sprite lostBackground;
    sf::Text lostText;

    // todo реализовать класс конпок. здесь добавить кнопки нормальные играть заново выйти в меню
};