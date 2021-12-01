#pragma once


//#include "GameContext.hpp"
//#include "AssetManager.hpp"
#include "GameState.hpp"
#include <memory>
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
    

    void draw() override;

private:
    sf::Music music;
    Button exit_button;
    Button play_button;
    Button mute_button;
    std::shared_ptr<GameContext> context;  // контекст игры с текстурами и шрифтами, бригаду тоже сюда добавьте
    sf::Sprite menuBackground;
    sf::Text playText; // пример
    // todo реализовать класс конпок. здесь добавить кнопки нормальные играть выйти там музыку вырубить
    // todo после нажатия играть переходим в коннектинг стейт и там нашаманьте после конектинга в геймстейт
};