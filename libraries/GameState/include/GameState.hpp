#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>

#include "State.hpp"
#include "GameContext.hpp"
#include "StateManager.hpp"
#include "PauseState.hpp"
#include "LostState.hpp"
#include "Tyan.hpp"
#include "Stone.hpp"
#include "Bullet.hpp"
#include "Button.hpp"
#include "Guardian.hpp"
#include "utils.hpp"

#define GETTING_HARDER_STEP 1

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

	void initStones(size_t new_stones, float speed_of_stones);

private:
    sf::Clock gameClock;
    std::shared_ptr<GameContext> context;

    float seconds_before_go_harder = 2;

    sf::Sprite background;

    Guardian guardian;

    Tyan tyan;

    std::vector<Bullet*> bulletsVec;

    std::vector<Stone*> stonesVec;
    size_t max_stones = 3;
    float max_speed_of_stones = 3;
    size_t new_stones_per_lvl = 2;
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