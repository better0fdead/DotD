#include <iostream>
#include "GameState.hpp"


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
    context->assets->addTexture(AssetID::BACKGROUND, "background.png", true);
    context->assets->addTexture(AssetID::TYAN, "tyan.png");
    context->assets->addTexture(AssetID::GUARDIAN, "guardian1.png");
    context->assets->addTexture(AssetID::BULLET, "fireball.png");
    context->assets->addTexture(AssetID::STONE, "stone.png");

    scoreText.setFont(context->assets->getFont(AssetID::MAIN_FONT));
    scoreText.setCharacterSize(40);
    scoreText.setOutlineColor(sf::Color::Black);
    scoreText.setOutlineThickness(1);
    scoreText.setString("Score: " + std::to_string(score));

    background.setTexture(context->assets->getTexture(AssetID::BACKGROUND));  // присваиваем текстурку нашему фону
    background.setTextureRect(context->window->getViewport(context->window->getDefaultView()));  // задаем границы

    //присваивем персонажам текстурки и ставим их в нужное место
    tyan->init(&context->assets->getTexture(AssetID::TYAN),
              sf::Vector2f(context->window->getSize().x / 2 + context->assets->getTexture(AssetID::TYAN).getSize().x / 2,
                           context->window->getSize().y / 2));

    guardian->init(&context->assets->getTexture(AssetID::GUARDIAN),
                  sf::Vector2f(context->window->getSize().x / 2 - context->assets->getTexture(AssetID::GUARDIAN).getSize().x / 2,
                               context->window->getSize().y / 2 - (context->assets->getTexture(AssetID::GUARDIAN).getSize().y -
                                                                   context->assets->getTexture(AssetID::TYAN).getSize().y) *
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
            for(auto & new_bullet : new_bullets){
                new_bullet->init(&context->assets->getTexture(AssetID::BULLET), new_bullet->getPos());

                bulletsVec.push_back(std::move(new_bullet));
            }
        }
    }
}


void GameState::processStuff() {
    // коллизии пуль и камней
    BullStonesCollisionHandler();

    //коллизии камней об песонажей
    StonesCharacterCollisionHandler();

    // сброс баффа через определенное время
    BuffDiscardHandler();

    score++;
}

void GameState::update(sf::Time deltaT) {
    player_guardian.send_msg("H0 3 0");
    GameOverCheck();

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

    for (auto & i : stonesVec) {
        i->update(deltaT);
    }

    GettingHarderHandler();  // усложняемся при определенных условиях

    if (player_guardian.recv_msg() == "2") {
        context->states->add(std::make_unique<LostState>(context, score), true);
    };
    if (player_guardian.recv_msg() == "3")
    {
        guardian->setState(STATES::fireBackwardsBuff);
    };
    scoreText.setString("score  " + std::to_string(score));
    player_guardian.send_msg_to_tyan(bulletsVec, std::move(stonesVec), 1, STATES::normal);
}

void GameState::draw() {
    // очищаем все потом рисуем все потихоньку а потом отображаем
    context->window->clear();
    context->window->draw(background);
    context->window->draw(*tyan);
    context->window->draw(*guardian);
    for (auto & bullet : bulletsVec) {
        context->window->draw(*bullet);
    }
    for (auto & stone : stonesVec) {
        context->window->draw(*stone);
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
        stonesVec.push_back(std::move(std::make_unique<Stone>(speed_of_stones)));
    }

    for (size_t i = current_stones; i < stonesVec.size(); i++) {
        stonesVec[i]->init(&context->assets->getTexture(AssetID::STONE), get_rand_pos_around_frame());
        stonesVec[i]->setDirection();
    }
}

void GameState::BullStonesCollisionHandler() {
    for (size_t i = 0; i < bulletsVec.size(); i++) {
        for (size_t j = 0; j < stonesVec.size(); j++) {
            if (bulletsVec[i]->getCollider().checkCollision(stonesVec[j]->getCollider())) {
                stonesVec.erase(stonesVec.begin() + j);
                if(guardian->checkState() != STATES::undestroyableBulletsBuff) {
                    bulletsVec.erase(bulletsVec.begin() + i);
                }
                score += POINTS_PER_STONE_DESTR;
            }
        }
    }
}

void GameState::StonesCharacterCollisionHandler() {
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
}

void GameState::BuffDiscardHandler(){
    if(guardian->checkState() != STATES::normal){
        if(buffClock.getElapsedTime() > sf::seconds(BUFF_DURATION)){
            guardian->setState(STATES::normal);
            buffClock.restart();
        }
    } else{
        buffClock.restart();
    }
}
void GameState::GameOverCheck() {
    if(guardian->isDead() || tyan->isDead()){
        context->window->clear();  // чищу окно
        player_guardian.send_msg("HO 3 1");
        context->states->add(std::make_unique<LostState>(context, score), true);
    }

}

void GameState::GettingHarderHandler() {
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
}
