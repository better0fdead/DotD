#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Button.hpp"
#include "SaveManager.hpp"

class MenuState: public State
{
public:
	MenuState();
	~MenuState();

	void update(double deltaTime) override; //Updates all the Components of the State
	void draw(sf::RenderWindow * w) override; //Draws all the Components of the State
	void processStuff(double deltaTime, sf::Vector2f mousePos) override; //Processes All the Components
	void switchState(State);

	void updateKeyBinds(double deltaTime) override; //Defines all the Keyboard Stuff for that state

private:
	void playBackgroundMusic(bool);
	void changeRole(bool);
	int getTopScore(std::string name);

	std::string name;

	sf::RectangleShape background; 

	sf::Font font;

	sf::Texture tScoreTexture;
	Button* topScoreButton; //Displays the Score 

	Button* changeRole;
	bool role;

	Button* muteSound;
	bool music;

	Button* play;

	Button* exit;


};