#pragma once


//#include "GameContext.hpp"
//#include "AssetManager.hpp"
#include "GameState.hpp"  //todo тут за херня убери лишнее
#include "LoadState.hpp"
#include "TyanState.hpp"
#include <memory>
#include "Button.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
class MenuState : public State {
public:
    MenuState(std::shared_ptr<GameContext> &context);

    ~MenuState();

    void init() override;

    void updateKeyBinds() override;

    void processStuff() override;

    void update(sf::Time deltaT) override;

    void draw() override;

private:
    sf::Music music;
    Button exit_button;
    Button play_button;
    Button mute_button;

private:
    std::shared_ptr<GameContext> context;  // контекст игры с текстурами и шрифтами, бригаду тоже сюда добавьте
    sf::Sprite menuBackground;
    sf::Text playText; // пример
    // todo реализовать класс конпок. здесь добавить кнопки нормальные играть выйти там музыку вырубить
    // todo после нажатия играть переходим в коннектинг стейт и там нашаманьте после конектинга в геймстейт
};