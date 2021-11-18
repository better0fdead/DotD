#include <gtest/gtest.h>
#include "Game.hpp"
#include "GameState.hpp"
#include "LostState.hpp"
#include "Entity.hpp"
#include "Collider.hpp"
#include "Guardian.hpp"
#include "Stone.hpp"
#include "Bullet.hpp"


TEST(Gamestart, GameStart){
    Game game;
    game.start();

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



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}