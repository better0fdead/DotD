#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

#include "GameContext.hpp"
#include "MenuState.hpp"

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
