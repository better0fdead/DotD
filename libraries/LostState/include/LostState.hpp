#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Button.hpp"


class LostState : public State {
public:
    LostState();

    ~LostState();

    void update(double deltaT) override;  //Updates the Components in the State

    void draw(sf::RenderWindow *w) override;  //Draws the Components in the State

    void processStuff(double deltaT, sf::Vector2f mousePos) override; //Processes the Components in the State

    void updateKeyBinds(double deltaT) override;  //Updates the Key presses in the State

    bool switchState() override; //Play again?

    void setScore(std::string newScore); //Displays the score

private:
    sf::Font font;
    int *score;

    sf::Text playerScore; //Displays the Score
    Button *playAgain;

    sf::RectangleShape background;
    sf::Texture backgroundTexture;

};