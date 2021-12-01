#pragma once

#include <memory>
#include "StateManager.hpp"
#include "AssetManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

enum AssetID {
    MAIN_FONT = 0, BACKGROUND, GUARDIAN, TYAN, STONE, BULLET,  PAUSE, LOST, MENU
};


struct GameContext {
    std::unique_ptr<AssetManager> assets;
    std::unique_ptr<StateManager> states;
    std::unique_ptr<sf::RenderWindow> window;

    GameContext() {
        assets = std::make_unique<AssetManager>();
        states = std::make_unique<StateManager>();
        window = std::make_unique<sf::RenderWindow>();
    }
};
