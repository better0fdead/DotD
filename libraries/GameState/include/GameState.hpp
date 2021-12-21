#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <ctime>
#include <memory>

#include "client.hpp"
#include "PauseState.hpp"
#include "LostState.hpp"
#include "Tyan.hpp"
#include "Stone.hpp"
#include "Guardian.hpp"

constexpr float GETTING_HARDER_STEP = 0.2;
constexpr uint8_t POINTS_PER_STONE_DESTR = 75;
constexpr uint8_t BUFF_DURATION = 10;

class GameState: public State
{
public:
	GameState(std::shared_ptr<GameContext> &context);
	~GameState();

    void init() override;  // про это все читать в State
    void updateKeyBinds() override;
    void processStuff() override;
    void update(sf::Time deltaT) override;
    void draw() override;

private:
    void pause();
    void initStones(size_t new_stones, float speed_of_stones);
    void BullStonesCollisionHandler();
    void StonesCharacterCollisionHandler();
    void BuffDiscardHandler();
    void GameOverCheck();
    void GettingHarderHandler();

    sf::Clock gameClock;
    sf::Clock buffClock;
    std::shared_ptr<GameContext> context;

    float seconds_before_go_harder = 2;

    sf::Sprite background;

    sf::Text scoreText;
    int score;

    std::unique_ptr<Guardian> guardian;

    std::unique_ptr<Tyan> tyan;

    std::vector<Bullet*> bulletsVec;

    std::vector<std::shared_ptr<Stone>> stonesVec;
    size_t max_stones = 3;
    float max_speed_of_stones = 3;
    size_t new_stones_per_lvl = 2;
    Client player_guardian;

};
