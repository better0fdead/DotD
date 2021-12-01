#include <iostream>
#include <random>
#include "GameState.hpp"
#include <ctime>
#include "Collider.hpp"

GameState::GameState(std::shared_ptr<GameContext> &context) : context(context) { // контекст подгружаем
    gameClock.restart();

    srand(time(nullptr));
}

GameState::~GameState() {

}

void GameState::init() {
    // добавляем текствурки в контекст
    context->assets->addTexture(BACKGROUND, "../assets/textures/background.png", true);
    context->assets->addTexture(TYAN, "../assets/textures/tyan.png");
    context->assets->addTexture(GUARDIAN, "../assets/textures/guardian1.png");
    context->assets->addTexture(BULLET, "../assets/textures/fireball.png");
    context->assets->addTexture(STONE, "../assets/textures/stone.png");

    background.setTexture(context->assets->getTexture(BACKGROUND));  // присваиваем текстурку нашему фону
    background.setTextureRect(context->window->getViewport(context->window->getDefaultView()));  // задаем границы

    //присваивем персонажам текстурки и ставим их в нужное место
    tyan.init(&context->assets->getTexture(TYAN),
              sf::Vector2f(context->window->getSize().x / 2 + context->assets->getTexture(TYAN).getSize().x / 2,
                           context->window->getSize().y / 2));

    guardian.init(&context->assets->getTexture(GUARDIAN),
                  sf::Vector2f(context->window->getSize().x / 2 - context->assets->getTexture(GUARDIAN).getSize().x / 2,
                               context->window->getSize().y / 2 - (context->assets->getTexture(GUARDIAN).getSize().y -
                                                                   context->assets->getTexture(TYAN).getSize().y) *
                                                                  0.5));

    // первые камешки
    initStones(max_stones, max_speed_of_stones);

}

void GameState::update(sf::Time deltaT) {
    // обновляем все компоненты игры по очереди
    tyan.update(deltaT);
    guardian.update(deltaT);
    for (size_t i = 0; i < bulletsVec.size(); i++) {
        if (bulletsVec[i]->getPos().x < 0 || bulletsVec[i]->getPos().y < 0 ||
            bulletsVec[i]->getPos().x > WINDOW_WIDTH ||
            bulletsVec[i]->getPos().y > WINDOW_HEIGHT) {
            bulletsVec.erase(bulletsVec.begin() + i);  // удаляем если пулька улетела за экран
            continue;
        }
        bulletsVec[i]->update(deltaT);
    }


    if (gameClock.getElapsedTime() > sf::seconds(seconds_before_go_harder)) {
        int go_harder = rand() % 4;
        if (!go_harder) {
            ++new_stones_per_lvl;  // со временем увеличиваем количество добавляемых камней за раз
        }
    }
    if (gameClock.getElapsedTime() > sf::seconds(seconds_before_go_harder)) {
        initStones(new_stones_per_lvl, max_speed_of_stones);  // новые камни
        max_speed_of_stones += 0.3;
        gameClock.restart();
        seconds_before_go_harder += GETTING_HARDER_STEP;  // шаг по времени усложнения увеличивается
    }

    for (size_t i = 0; i < stonesVec.size(); i++) {
        stonesVec[i]->update(deltaT);
    }

}

void GameState::draw() {
    // очищаем все потом рисуем все потихоньку а потом отображаем
    context->window->clear();
    context->window->draw(background);
    context->window->draw(tyan);
    context->window->draw(guardian);
    for (size_t i = 0; i < bulletsVec.size(); i++) {
        context->window->draw(*bulletsVec[i]);
    }
    for (size_t i = 0; i < stonesVec.size(); i++) {
        context->window->draw(*stonesVec[i]);
    }
    context->window->display();

}

void GameState::processStuff() {
    for (size_t i = 0; i < bulletsVec.size(); i++) {
        for (size_t j = 0; j < stonesVec.size(); j++) {
            if (bulletsVec[i]->getCollider().checkCollision(stonesVec[j]->getCollider()) == true) {
                bulletsVec.erase(bulletsVec.begin() + i);
                stonesVec.erase(stonesVec.begin() + j);
            }
        }
    }

    for (size_t j = 0; j < stonesVec.size(); j++) {
        if (tyan.getCollider().checkCollision(stonesVec[j]->getCollider()) == true) {
            stonesVec.erase(stonesVec.begin() + j);
            tyan.takeDamage();
            context->states->add(std::make_unique<LostState>(context), true);
        }
    }

    for (size_t j = 0; j < stonesVec.size(); j++) {
        if (guardian.getCollider().checkCollision(stonesVec[j]->getCollider()) == true) {
            stonesVec.erase(stonesVec.begin() + j);
            guardian.takeDamage();
            context->states->add(std::make_unique<LostState>(context), true);

        }
    }


    sf::Event event;  // то же что и в меню, там почитайте
    while (context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            context->window->close();
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Tilde:
                    context->window->close();
                    break;
                case sf::Keyboard::Escape:
                    context->states->add(std::make_unique<PauseState>(context));
                    break;
                default:
                    break;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) { // стреляем по нажатию
            auto bul = guardian.shoot((sf::Vector2f) sf::Mouse::getPosition(*context->window));
            bul->init(&context->assets->getTexture(BULLET), bul->getPos());
            bulletsVec.push_back(bul);
        }

    }

}

void GameState::pause() {
}

void GameState::start() {
}

void GameState::initStones(size_t new_stones, float speed_of_stones) {
    auto current_stones = stonesVec.size();
    for (size_t i = 0; i < new_stones; i++) {
        stonesVec.push_back(new Stone(speed_of_stones));
    }

    for (size_t i = current_stones; i < stonesVec.size(); i++) {
        stonesVec[i]->init(&context->assets->getTexture(STONE), get_rand_pos_around_frame());
        stonesVec[i]->setDirection();
//        std::cout << stonesVec[i].getPos().x << " " << stonesVec[i].getPos().y << std::endl;
    }

}
