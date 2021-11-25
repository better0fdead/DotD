#pragma once

#include "AssetManager.hpp"
#include "StateManager.hpp"
#include "GameContext.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include "MenuState.hpp"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800



class Game {
public:
    Game();

    ~Game();

    void start(); // starts the Game

private:
    //    void update();  // updates all components in game
    //    void draw();  // draws all Components in game
    //    void processStuff();  // processes all components in game
    //    void run();  // main Loop

    //    void initStates();  // init all the States of the Game

private:
    std::shared_ptr<GameContext> context; // контекст с тексурками и шрифтами,
    // его передаем в состояния

    const sf::Time deltaT = sf::seconds(1.f / 60.f); // 1/FPS

    //    std::vector<State *> states;  // holds all the States in the Game
    //    int score;
};