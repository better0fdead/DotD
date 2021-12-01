#pragma once

#include "AssetManager.hpp"
#include "StateManager.hpp"
#include "GameContext.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include "MenuState.hpp"
#include "GameState.hpp"
//#include "Collider.hpp"


class Game {
public:
    Game();

    ~Game();

    void start(); // starts the Game

private:
    std::shared_ptr<GameContext> context; // контекст с тексурками и шрифтами,
    // его передаем в состояния

    const sf::Time deltaT = sf::seconds(1.f / 60.f); // 1/FPS

};