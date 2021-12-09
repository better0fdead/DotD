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




TEST(TAKE_DAMAGE_TEST, DEAD){
    auto guardianTexture = new sf::Texture;
    guardianTexture->loadFromFile("../assets/textures/guardian1.png");

    Guardian guardian;
    guardian.init(guardianTexture, sf::Vector2f(50,50));

    guardian.takeDamage();

    auto tyanTexture = new sf::Texture;
    tyanTexture->loadFromFile("../assets/textures/tyan.png");

    Tyan tyan;
    tyan.init(tyanTexture, sf::Vector2f(100,100));

    tyan.takeDamage();
    EXPECT_TRUE(guardian.isDead());
    EXPECT_TRUE(tyan.isDead());  // w/o buffs characters have 1hp

    delete guardianTexture;
    delete tyanTexture;

}

TEST(INIT_TEST, Positioning_test){
    auto guardianTexture = new sf::Texture;
    guardianTexture->loadFromFile("../assets/textures/guardian1.png");

    Guardian guardian;
    guardian.init(guardianTexture, sf::Vector2f(50,50));


    auto tyanTexture = new sf::Texture;
    tyanTexture->loadFromFile("../assets/textures/tyan.png");

    Tyan tyan;
    tyan.init(tyanTexture, sf::Vector2f(100,100));

    EXPECT_TRUE(guardian.getPos() == sf::Vector2f(50,50));
    EXPECT_TRUE(tyan.getPos() == sf::Vector2f(100,100));

    delete guardianTexture;
    delete tyanTexture;
}

TEST(POSITIONING, Set_pos){
    auto guardianTexture = new sf::Texture;
    guardianTexture->loadFromFile("../assets/textures/guardian1.png");

    Guardian guardian;
    guardian.init(guardianTexture, sf::Vector2f(50,50));
    EXPECT_TRUE(guardian.getPos() == sf::Vector2f(50,50));

    guardian.setPos({100, 100});
    EXPECT_TRUE(guardian.getPos() == sf::Vector2f(100,100));

    delete guardianTexture;
}

TEST(COLLISION, col1){
    auto guardianTexture = new sf::Texture;
    guardianTexture->loadFromFile("../assets/textures/guardian1.png");

    Guardian guardian;
    guardian.init(guardianTexture, sf::Vector2f(50,50));


    auto tyanTexture = new sf::Texture;
    tyanTexture->loadFromFile("../assets/textures/tyan.png");

    Tyan tyan;
    tyan.init(tyanTexture, sf::Vector2f(60,60));
    tyan.update(sf::seconds(1));

    EXPECT_TRUE(guardian.getCollider().checkCollision(tyan.getCollider()));
    EXPECT_TRUE(tyan.getCollider().checkCollision(guardian.getCollider()));

    tyan.setPos(sf::Vector2f(500,500));
    EXPECT_FALSE(tyan.getCollider().checkCollision(guardian.getCollider()));

    delete guardianTexture;
    delete tyanTexture;
}

TEST(COLLISION, col2){
    auto guardianTexture = new sf::Texture;
    guardianTexture->loadFromFile("../assets/textures/guardian1.png");

    Guardian guardian;
    guardian.init(guardianTexture, sf::Vector2f(50,50));


    auto tyanTexture = new sf::Texture;
    tyanTexture->loadFromFile("../assets/textures/tyan.png");

    Tyan tyan;
    tyan.init(tyanTexture, sf::Vector2f(60,60));

    auto stoneTexture = new sf::Texture;
    stoneTexture->loadFromFile("../assets/textures/stone.png");

    Stone stone(5);
    stone.init(stoneTexture, sf::Vector2f(55,55));

    EXPECT_TRUE(guardian.getCollider().checkCollision(stone.getCollider()));
    EXPECT_TRUE(tyan.getCollider().checkCollision(stone.getCollider()));

    delete guardianTexture;
    delete tyanTexture;
    delete stoneTexture;
}

TEST(COLLISION, col3){
    auto stoneTexture = new sf::Texture;
    stoneTexture->loadFromFile("../assets/textures/stone.png");

    Stone stone(5);
    stone.init(stoneTexture, sf::Vector2f(55,55));


    auto bulletTexture = new sf::Texture;
    bulletTexture->loadFromFile("../assets/textures/fireball.png");

    Bullet bullet(sf::Vector2f(55,55),sf::Vector2f(0,0));
    bullet.init(bulletTexture, sf::Vector2f(55,55));

    EXPECT_TRUE(bullet.getCollider().checkCollision(stone.getCollider()));
    EXPECT_TRUE(stone.getCollider().checkCollision(bullet.getCollider()));

    delete stoneTexture;
    delete bulletTexture;
}

TEST(COLLISION, col4_getpos){
    auto stoneTexture = new sf::Texture;
    stoneTexture->loadFromFile("../assets/textures/stone.png");

    Stone stone(5);
    stone.init(stoneTexture, sf::Vector2f(55,55));

    EXPECT_TRUE(stone.getPos() == stone.getCollider().getPos());
    delete stoneTexture;
}

TEST(SHOOTING, shooting){
    auto guardianTexture = new sf::Texture;
    guardianTexture->loadFromFile("../assets/textures/guardian1.png");

    Guardian guardian;
    guardian.init(guardianTexture, sf::Vector2f(50,50));

    auto bullet = guardian.shoot({95, 50});

    EXPECT_TRUE(bullet[0]->getPos() == sf::Vector2f(50 + DELTA_X_FOR_BULLET, 50 + DELTA_Y_FOR_BULLET));

    bullet[0]->update(sf::seconds(1));

    EXPECT_TRUE(bullet[0]->getPos() == sf::Vector2f(50 + DELTA_X_FOR_BULLET, 50 + DELTA_Y_FOR_BULLET + DEFAULT_SPEED));
    delete guardianTexture;
}

TEST(BULLET_BUFFS, SpeedBuff){
    auto guardianTexture = new sf::Texture;
    guardianTexture->loadFromFile("../assets/textures/guardian1.png");

    Guardian guardian(bulletSpeedBuff);
    guardian.init(guardianTexture, sf::Vector2f(50,50));

    auto bullet = guardian.shoot({95, 50});

    bullet[0]->update(sf::seconds(1));

    EXPECT_TRUE(bullet[0]->getPos() == sf::Vector2f(50 + DELTA_X_FOR_BULLET, 50 + DELTA_Y_FOR_BULLET + SPEED_BUFF_COEFF * DEFAULT_SPEED));
    delete guardianTexture;
}

TEST(UTILS, rand_in_centre){
    sf::Vector2f pos_in_centre = get_rand_pos_in_centre();

    EXPECT_TRUE(pos_in_centre.x >= WINDOW_WIDTH / 2 - CENTRE_INTERVAL && pos_in_centre.x <= WINDOW_WIDTH / 2 + CENTRE_INTERVAL);
    EXPECT_TRUE(pos_in_centre.y >= WINDOW_HEIGHT / 2 - CENTRE_INTERVAL && pos_in_centre.y <= WINDOW_HEIGHT / 2 + CENTRE_INTERVAL);
}

TEST(UTILS, rand_around_frame){
    srand(time(nullptr));

    sf::Vector2f pos_frame1 = get_rand_pos_around_frame();

    EXPECT_TRUE(pos_frame1.x >= -200  && pos_frame1.x <= WINDOW_WIDTH + 200);
    EXPECT_TRUE(pos_frame1.y >= -200 && pos_frame1.y <= WINDOW_HEIGHT + 200);

    sf::Vector2f pos_frame2 = get_rand_pos_around_frame();

    EXPECT_TRUE(pos_frame2.x >= -200  && pos_frame2.x <= WINDOW_WIDTH + 200);
    EXPECT_TRUE(pos_frame2.y >= -200 && pos_frame2.y <= WINDOW_HEIGHT + 200);

    sf::Vector2f pos_frame3 = get_rand_pos_around_frame();

    EXPECT_TRUE(pos_frame3.x >= -200  && pos_frame3.x <= WINDOW_WIDTH + 200);
    EXPECT_TRUE(pos_frame3.y >= -200 && pos_frame3.y <= WINDOW_HEIGHT + 200);

    sf::Vector2f pos_frame4 = get_rand_pos_around_frame();

    EXPECT_TRUE(pos_frame4.x >= -200  && pos_frame4.x <= WINDOW_WIDTH + 200);
    EXPECT_TRUE(pos_frame4.y >= -200 && pos_frame4.y <= WINDOW_HEIGHT + 200);

    sf::Vector2f pos_frame5 = get_rand_pos_around_frame();

    EXPECT_TRUE(pos_frame5.x >= -200  && pos_frame5.x <= WINDOW_WIDTH + 200);
    EXPECT_TRUE(pos_frame5.y >= -200 && pos_frame5.y <= WINDOW_HEIGHT + 200);

}

TEST(STONE, update_move){
    auto stoneTexture = new sf::Texture;
    stoneTexture->loadFromFile("../assets/textures/stone.png");

    Stone stone(5);
    stone.init(stoneTexture, sf::Vector2f(0,0));

    stone.update(sf::seconds(1));
    EXPECT_TRUE(stone.getPos() == sf::Vector2f(0, 0));  // без заданного направления камень не движется

    stone.setDirection();
    stone.update(sf::seconds(1));
    EXPECT_TRUE(stone.getPos() != sf::Vector2f(0, 0));  // а тут уже движется
    auto intermPos = stone.getPos();

    stone.setPos({1600, 200});
    stone.update(sf::seconds(1));
    EXPECT_TRUE(stone.getPos() != intermPos);
    intermPos = stone.getPos();

    stone.setDirection();
    stone.update(sf::seconds(1));
    EXPECT_TRUE(stone.getPos() != intermPos);
    intermPos = stone.getPos();

    stone.setPos({800, 1600});
    stone.setDirection();
    stone.update(sf::seconds(1));
    EXPECT_TRUE(stone.getPos() != intermPos);
    intermPos = stone.getPos();

    stone.setPos({800, -400});
    stone.setDirection();
    stone.update(sf::seconds(1));
    EXPECT_TRUE(stone.getPos() != intermPos);

    delete stoneTexture;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}