#include "PauseState.hpp"

PauseState::PauseState(std::shared_ptr<GameContext> &context) : context(context) {

}

PauseState::~PauseState() {

}

void PauseState::init() {
    context->assets->addTexture(AssetID::PAUSE, "b2.png");
    pauseBackground.setTexture(context->assets->getTexture(AssetID::PAUSE));  // присваиваем текстурку нашему фону
    pauseBackground.scale({1.17, 1.1});
    pauseBackground.setColor(sf::Color(255, 255, 255, 170));
    context->window->draw(pauseBackground);


    pauseText.setFont(context->assets->getFont(AssetID::MAIN_FONT));  // применяем шрифт к тексту
    pauseText.setFillColor(sf::Color::Black);
    pauseText.setOutlineThickness(0.5);
    pauseText.setOutlineColor(sf::Color::White);
    pauseText.setString("game is paused");  // добавляем в текст нашу строку


    pauseText.setOrigin(pauseText.getLocalBounds().width / 2,
                        pauseText.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    pauseText.setPosition(context->window->getSize().x / 2,
                          context->window->getSize().y / 3);  // центрируем текст
}

void PauseState::updateKeyBinds() {
    sf::Event event;  // про ивенты почитайте
    while (context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {  // если на крестик нажали
            context->window->close();
        }
        if (event.type == sf::Event::KeyPressed) {  // если кнопку нажали
            switch (event.key.code) {
                case sf::Keyboard::Escape:  // если нажали ескейп то вышли из паузы
                    resume();
                    break;
                case sf::Keyboard::Tilde:  // если тильда то закрываемся
                    context->window->close();
                    break;
                default:
                    break;
            }
        }
    }
}

void PauseState::processStuff() {

}

void PauseState::update(sf::Time deltaT) {

}

void PauseState::draw() {
    context->window->draw(pauseText);  // рисую текст
    context->window->display();  // отображаю все что нарисовал
}

void PauseState::resume() {
    context->states->popCurrent();
}
