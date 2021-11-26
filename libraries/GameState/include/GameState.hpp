#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>

#include "State.hpp"
#include "GameContext.hpp"
#include "StateManager.hpp"
#include "Tyan.hpp"
#include "Stone.hpp"
#include "Bullet.hpp"
#include "Button.hpp"
#include "Guardian.hpp"

class GameState: public State
{
public:
	GameState(std::shared_ptr<GameContext> &context);
	~GameState();

    void init() override;  // про это все читать в State
	void update(sf::Time deltaT) override;
	void draw() override;
	void processStuff() override;

    void pause() override;
    void start() override;

	void initStones();

private:
    std::shared_ptr<GameContext> context;

    sf::Sprite background;

    Guardian guardian;
	sf::Texture guardianTexture;

    Tyan tyan;
	sf::Texture tyanTexture;

//	sf::Texture stoneTexture;

//
//	std::vector<Button *> stones;
    // // counters For Collision
    // double counterBS;
    // double counterST;
    // double counterSG;


	// double pauseCounter;
//	sf::Font font;
//
//	sf::Texture scoreTexture;
//	Button* scoreButton;
};