#include "Game.hpp"

Game::Game() : context(std::make_shared<GameContext>()) {
    context->window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "DotT");
    // todo add first state(menu) to states here
    context->states->add(std::make_unique<MenuState>(context)); // начинаем с меню
}

Game::~Game() {}

void Game::start() {

    sf::Clock clock;                              // запуск часов
    sf::Time timeSinceLastFrame = sf::Time::Zero; // время с прошлого кадра

    while (context->window->isOpen()) {
        timeSinceLastFrame += clock.restart(); //пока окно открыто увеличиваем счетчик каждый
        //псевдокадр (тик когда мы могли бы обновить все, но не делаем этого)

        while (timeSinceLastFrame > deltaT) { // как только оно достигает нужного нам значения(1/60 секунды)
            // у нас запускается логика всякая и отрисовывается все
            timeSinceLastFrame -= deltaT;

            context->states->switchStateIfNeeded();  // переключаемся на текущее состояние(или остаемся)
            context->states->getCurrentState()->updateKeyBinds();  // чекаем кнопки в состоянии
            context->states->getCurrentState()->processStuff();  // чекаем коллизии и состояния объектов
            context->states->getCurrentState()->update(deltaT);  // обновляем данные
            context->states->getCurrentState()->draw();  //рисуем

        }
    }
}
