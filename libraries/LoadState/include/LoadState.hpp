#pragma once


//#include "GameContext.hpp"
//#include "AssetManager.hpp"
#include "GameState.hpp"
#include <memory>
#include "Button.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include "Connecting.hpp"
#include "client.hpp"
class LoadState : public State {
public:
    LoadState(std::shared_ptr<GameContext> &context);

    ~LoadState();

    void init() override;

    void updateKeyBinds() override;

    void processStuff() override;

    void update(sf::Time deltaT) override;

    

    void draw() override;

private:
    sf::Music music;
    Button exit_button;
    Button play_button;
    Button Tyan_button;
    Button Guardian_button;
    Button mute_button;
    sf::Texture loadtex;
    std::shared_ptr<GameContext> context;  // контекст игры с текстурами и шрифтами, бригаду тоже сюда добавьте
    sf::Sprite menuBackground;
    sf::Text playText; // пример
    Client player_guardian;
    Client player_tyan;
    // todo реализовать класс конпок. здесь добавить кнопки нормальные играть выйти там музыку вырубить
    // todo после нажатия играть переходим в коннектинг стейт и там нашаманьте после конектинга в геймстейт
};