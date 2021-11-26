#include "GameState.hpp"

GameState::GameState(std::shared_ptr<GameContext> &context) : context(context) { // контекст подгужаем

}

GameState::~GameState() {

}

void GameState::init() {
    // добавляем текствурки в контекст
    context->assets->addTexture(BACKGROUND, "../assets/textures/background.png", true);
    context->assets->addTexture(TYAN, "../assets/textures/tyan.png");
    context->assets->addTexture(GUARDIAN, "../assets/textures/guardian1.png");
    context->assets->addTexture(BULLET, "../assets/textures/fireball.png");

    background.setTexture(context->assets->getTexture(BACKGROUND));  // присваиваем текстурку нашему фону
    background.setTextureRect(context->window->getViewport(context->window->getDefaultView()));  // задаем границы

    //присваивем персонажам текстурки и ставим их в нужное место
    tyan.init(&context->assets->getTexture(TYAN),
              sf::Vector2f(context->window->getSize().x / 2 + 75, context->window->getSize().y / 2));

    guardian.init(&context->assets->getTexture(GUARDIAN),
                  sf::Vector2f(context->window->getSize().x / 2 - 75, context->window->getSize().y / 2 - 13));
}

void GameState::update(sf::Time deltaT) {

}

void GameState::draw() {
    // очищаем все потом рисуем все потихоньку а потом отображаем
    context->window->clear();
    context->window->draw(background);
    context->window->draw(tyan);
    context->window->draw(guardian);
    context->window->display();

}

void GameState::processStuff() {
    sf::Event event;  // то же что и в меню, там почитайте
    while (context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            context->window->close();
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Escape:
                    context->window->close();
                    break;
                default:
                    break;
            }
        }
    }

}

void GameState::pause() {
}

void GameState::start() {
}

void GameState::initStones() {

}
