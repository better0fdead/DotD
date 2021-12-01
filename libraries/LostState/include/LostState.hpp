#pragma once


#include "State.hpp"
#include "StateManager.hpp"
#include "GameContext.hpp"
#include "MenuState.hpp"
#include "GameState.hpp"
#include <memory>

class LostState : public State {
public:
    LostState(std::shared_ptr<GameContext> &context);

    ~LostState();

    void init() override;

    void update(sf::Time deltaT) override;  //Updates the Components in the State

    void draw() override;  //Draws the Components in the State

    void processStuff() override; //Processes the Components in the State

//    void updateKeyBinds(double deltaT) override;  //Updates the Key presses in the State

//    bool switchState() override; //Play again?

//    void setScore(std::string newScore); //Displays the score

private:
    std::shared_ptr<GameContext> context;  // контекст игры с текстурами и шрифтами, бригаду тоже сюда добавьте

//    int *score;

//    sf::Text playerScore; //Displays the Score
//    Button *playAgain;

    sf::Sprite lostBackground;
    sf::Text lostText;

};