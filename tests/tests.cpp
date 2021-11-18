#include <gtest/gtest.h>
#include "Game.hpp"
#include "GameState.hpp"
#include "LostState.hpp"
#include "Entity.hpp"
#include "Collider.hpp"
#include "Guardian.hpp"
#include "Stone.hpp"
#include "Bullet.hpp"
#include "Tyan.hpp"
#include "MenuState.hpp"
#include "SaveManager.hpp"
#include "Tasks.hpp"

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

TEST(SaveManager, save_good)
{
    int score = 10;
    std::string name = "Fedya";
    EXPECT_TRUE(SaveScore(score, name));
}

TEST(SaveManager, save_false)
{
    int score = -10;
    std::string name = "Fedya";
    EXPECT_FALSE(SaveScore(score, name));
}

TEST(SaveManager, get_score_good)
{
    std::string name = "test_good";
    EXPECT_EQ(getTopScore(name), 1);
}


TEST(SaveManager, get_score_invalid_name)
{
    std::string name = "test_bad";
    EXPECT_EQ(getTopScore(name), -1);
}

TEST(Tasks, solveTask_solved)
{
    int num = 1;
    EXPECT_TRUE(solveTask(num));
}

TEST(Tasks, solveTask_not_solved)
{
    int num = 1;
    EXPECT_FALSE(solveTask(num));
}

TEST(Tasks, solveTask_bad_num)
{
    int num = -1;
    EXPECT_FALSE(solveTask(num));
}

TEST(MenuState, changeRole_guardian)
{
    EXPECT_TRUE(changeRole(TRUE) == 1);
}

TEST(MenuState, changeRole_tyan)
{
    EXPECT_TRUE(changeRole(TRUE) == 0);
}

TEST(MenuState, playBackgroundMusic_play)
{
    EXPECT_TRUE(playBackgroundMusic(TRUE) == 1)
}


TEST(MenuState, playBackgroundMusic_mute)
{
    EXPECT_TRUE(playBackgroundMusic(FALSE) == 0)
}


TEST(MenuState,getTopScore_good)
{
    std::string name = "test_good";
    EXPECT_EQ(getTopScore(name), 1);
}

TEST(MenuState,getTopScore_good)
{
    std::string name = "test_bad";
    EXPECT_EQ(getTopScore(name), 0);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}