#pragma once

#include <memory>
#include "StateManager.hpp"
#include "AssetManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

constexpr uint16_t WINDOW_WIDTH = 1200;
constexpr uint16_t WINDOW_HEIGHT = 800;


enum class STATES{normal = 0, fireBackwardsBuff, bulletSpeedBuff, hpUpBuff, bulletSizeBuff, undestroyableBulletsBuff};


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
