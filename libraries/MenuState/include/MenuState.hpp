#pragma once
#include "State.hpp"
#include "GameContext.hpp"
#include "StateManager.hpp"
#include <memory>

#include <SFML/Graphics/Text.hpp>

class MenuState : public State {
public:
    MenuState(std::shared_ptr<GameContext>& context);

    ~MenuState();

    void init() override;

    void update() override;
    void draw() override;
    void processStuff() override;
    void updateKeyBinds() override;

private:
std::shared_ptr<GameContext> context;
sf::Text playText;
};