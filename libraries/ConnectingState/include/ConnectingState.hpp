#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Button.hpp"


class ConnectingState : public State {
public:
    ConnectingState();

    ~ConnectingState();

    void update(double deltaT) override;  //Updates the Components in the State

    void draw(sf::RenderWindow *w) override;  //Draws the Components in the State

    void processStuff(double deltaT, sf::Vector2f mousePos) override; //Processes the Components in the State

    void updateKeyBinds(double deltaT) override;  //Updates the Key presses in the State

    bool switchState() override; //Play again?



private:
    std::string friendIP;
    std::boolean role;

    sf::Font font;

    Button *changeRole;
    Button *exit;
    Button *backToMenu;


    sf::RectangleShape background;
    sf::Texture backgroundTexture;

};