#pragma once

#include <SFML/Graphics.hpp>


class State
{
public:
	State();
	~State();
	

	virtual void update(double deltaT) = 0; //Updates the Components of the State
	virtual void draw(sf::RenderWindow * w) = 0; //Draws the Components of the State
	virtual void processStuff(double deltaT , sf::Vector2f mousePos) = 0;//Process The Components in the State
	virtual void updateKeyBinds(double deltaT) = 0; //All Key Binds Of State go in here 

	// virtual void checkForQuit(); //Predefined Quit Key

	void setQuit(bool newQuit);
	bool getQuit() const; // determines if State should end Goes in Update Function in GAME

	void setHolderScore(int newScore);
	int getHolderScore() const;

	//Allows the States the Option to switch to a diffent State depending on their definitions 
	virtual bool switchState();

private:
	bool quit;  // determines if the State Should Quit Initially False
	// int holderScore; // transfer score from GameState to LostState
	
};
