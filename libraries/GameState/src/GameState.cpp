#include <iostream>
#include <random>
#include "GameState.hpp"
#include <ctime>
#include "Collider.hpp"

GameState::GameState(std::shared_ptr<GameContext> &context) : context(context), score(0) { // контекст подгружаем
    gameClock.restart();
    buffClock.restart();

    guardian = std::make_unique<Guardian>();
    tyan = std::make_unique<Tyan>();

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

    scoreText.setFont(context->assets->getFont(MAIN_FONT));
    scoreText.setCharacterSize(40);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setOutlineThickness(1);
    scoreText.setString("Score: " + std::to_string(score));

    background.setTexture(context->assets->getTexture(BACKGROUND));  // присваиваем текстурку нашему фону
    background.setTextureRect(context->window->getViewport(context->window->getDefaultView()));  // задаем границы

    //присваивем персонажам текстурки и ставим их в нужное место
    tyan->init(&context->assets->getTexture(TYAN),
              sf::Vector2f(context->window->getSize().x / 2 + context->assets->getTexture(TYAN).getSize().x / 2,
                           context->window->getSize().y / 2));

    guardian->init(&context->assets->getTexture(GUARDIAN),
                  sf::Vector2f(context->window->getSize().x / 2 - context->assets->getTexture(GUARDIAN).getSize().x / 2,
                               context->window->getSize().y / 2 - (context->assets->getTexture(GUARDIAN).getSize().y -
                                                                   context->assets->getTexture(TYAN).getSize().y) *
                                                                  0.5));

    // первые камешки
    initStones(max_stones, max_speed_of_stones);

}


void GameState::updateKeyBinds() {
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
                    pause();
                    break;
                default:
                    break;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) { // стреляем по нажатию
            auto new_bullets = guardian->shoot((sf::Vector2f) sf::Mouse::getPosition(*context->window));
            for(size_t i = 0; i < new_bullets.size(); i++){
                new_bullets[i]->init(&context->assets->getTexture(BULLET), new_bullets[i]->getPos());

                bulletsVec.push_back(new_bullets[i]);
            }

        }

    }
}


void GameState::processStuff() {
    // коллизии пуль и камней
    for (size_t i = 0; i < bulletsVec.size(); i++) {
        for (size_t j = 0; j < stonesVec.size(); j++) {
            if (bulletsVec[i]->getCollider().checkCollision(stonesVec[j]->getCollider()) == true) {
                stonesVec.erase(stonesVec.begin() + j);
                if(guardian->checkState() != undestroyableBulletsBuff) {
                    bulletsVec.erase(bulletsVec.begin() + i);
                }
                score += POINTS_PER_STONE_DESTR;
            }
        }
    }

    //коллизии камней об песонажей
    for (size_t j = 0; j < stonesVec.size(); j++) {
        if (tyan->getCollider().checkCollision(stonesVec[j]->getCollider()) == true) {
            stonesVec.erase(stonesVec.begin() + j);
            tyan->takeDamage();
        }
    }
    for (size_t j = 0; j < stonesVec.size(); j++) {
        if (guardian->getCollider().checkCollision(stonesVec[j]->getCollider()) == true) {
            stonesVec.erase(stonesVec.begin() + j);
            guardian->takeDamage();
        }
    }

    // сброс баффа через определенное время
    if(guardian->checkState() != 0){
        if(buffClock.getElapsedTime() > sf::seconds(BUFF_DURATION)){
            guardian->setState(0);
            buffClock.restart();
        }
    } else{
        buffClock.restart();
    }

    score++;
}

void GameState::update(sf::Time deltaT) {
    if(guardian->isDead() || tyan->isDead()){
        context->window->clear();  // чищу окно
        send_msg("HO 3 1");
        context->states->add(std::make_unique<LostState>(context, score), true);
    }

    // обновляем все компоненты игры по очереди
    tyan->update(deltaT);
    guardian->update(deltaT);
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

    send_msg("H0 3 0");
    if (recv_msg() == "2") {
        context->states->add(std::make_unique<LostState>(context, score), true);
    };
    if (recv_msg() == "3")
    {
        guardian.GuardianState = 2;
    };
    scoreText.setString("score  " + std::to_string(score));
}

void GameState::draw() {
    // очищаем все потом рисуем все потихоньку а потом отображаем
    context->window->clear();
    context->window->draw(background);
    context->window->draw(*tyan);
    context->window->draw(*guardian);
    for (size_t i = 0; i < bulletsVec.size(); i++) {
        context->window->draw(*bulletsVec[i]);
    }
    for (size_t i = 0; i < stonesVec.size(); i++) {
        context->window->draw(*stonesVec[i]);
    }
    context->window->draw(scoreText);
    context->window->display();

}

void GameState::pause() {
    context->states->add(std::make_unique<PauseState>(context));
}

void GameState::initStones(size_t new_stones, float speed_of_stones) {
    auto current_stones = stonesVec.size();
    for (size_t i = 0; i < new_stones; i++) {
        stonesVec.push_back(new Stone(speed_of_stones));
    }

    for (size_t i = current_stones; i < stonesVec.size(); i++) {
        stonesVec[i]->init(&context->assets->getTexture(STONE), get_rand_pos_around_frame());
        stonesVec[i]->setDirection();
    }
}
