#pragma once


#include <SFML/Graphics.hpp>
#include <stack>
#include <string>
#include "Entity.hpp"
#include "GameState.hpp"
#include "Guardian.hpp"
#include "Tyan.hpp"
#include "Button.hpp"
#include "LostState.hpp"

class Game {
public:
    Game();

    ~Game();

    void start(); // starts the Game

private:
    void update();  // updates all components in game
    void draw();  // draws all Components in game
    void processStuff();  // processes all components in game
    void run();  // main Loop

    void initStates();  // init all the States of the Game

private:
    sf::RenderWindow window; // game window

    std::stack<State *> states;  // holds all the States in the Game

    double deltaT;  // time since last frame
    int score;

};