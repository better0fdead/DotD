#include <gtest/gtest.h>
#include "Game.hpp"
#include "GameState.hpp"
#include "LostState.hpp"
#include "Entity.hpp"
#include "Collider.hpp"
#include "Guardian.hpp"
#include "Stone.hpp"
#include "Bullet.hpp"


TEST(Taking_damage, Taking_damage){
    Guardian guardian(sf::Vector2f(50, 50), sf::Texture());
    guardian.takeDamage();

    Tyan tyan(sf::Vector2f(20, 20), "tyanTexture.png");
    tyan.takeDamage();
    EXPECT_TRUE(guardian.isDead());
    EXPECT_TRUE(tyan.isDead());  // w/o buffs characters have 1hp
}

TEST(Positioning_test, Positioning_test){
    Guardian guardian(sf::Vector2f(50, 50), "guardianTexture.png");
    EXPECT_TRUE(guardian.getPos() == sf::Vector2f(50, 50));
    guardian.setPos(sf::Vector2f(20, 20));
    EXPECT_TRUE(guardian.getPos() == sf::Vector2f(20, 20));
}

TEST(Collision, Collision_test) {
    Guardian guardian(sf::Vector2f(50, 50), "guardianTexture.png");
    Stone stone(sf::Vector2f(50, 50), "stoneTexture.png");

    EXPECT_TRUE(guardian.getCollider().checkCollision(stone.getCollider()));
}

TEST(Collision, Collision_test2) {
    Bullet bullet(sf::Vector2f(50, 50), "bulletTexture.png");
    Stone stone(sf::Vector2f(50, 50), "stoneTexture.png");

    EXPECT_TRUE(bullet.getCollider().checkCollision(stone.getCollider()));
}


TEST(End_GameState, End_GameState){
    GameState* gameState;
    LostState* lostState;
    Vector<State*> states = {lostState, gameState};

    Guardian guardian(sf::Vector2f(50, 50), "guardianTexture.png");
    guardian.takeDamage();

    EXPECT_TRUE(states.back() == lostState);  // wont work!!
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}