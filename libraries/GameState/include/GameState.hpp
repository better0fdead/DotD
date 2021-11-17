#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Guardian.hpp"
#include "Tyan.hpp"
#include "Stone.hpp"
#include "Button.hpp"


class GameState: public State
{
public:
	GameState();
	~GameState();

	void update(double deltaTime) override; //Updates all the Components of the State
	void draw(sf::RenderWindow * w) override; //Draws all the Components of the State
	void processStuff(double deltaTime, sf::Vector2f mousePos) override; //Processes All the Components (check Collision etc)

	void updateKeyBinds(double deltaTime) override; //Defines all the Keyboard Stuff for that state

	void initStones(); //Initializes the stones 

private:
	Guardian * guardian;
	sf::Texture guardianTexture;

	Tyan * tyan;
	sf::Texture tyanTexture;

	std::vector<Stone *> stones;  
	sf::Texture stoneTexture;

	// // counters For Collision
	// double counterBS;
	// double counterST;
	// double counterSG;
	// double pauseCounter;


	sf::RectangleShape background; 

	bool pause; //Pauses the Screen

	sf::Font font;

	sf::Texture scoreTexture;
	Button* scoreButton; //Displays the Score 

};