#include "PauseState.hpp"

PauseState::PauseState(std::shared_ptr<GameContext> &context) : context(context) {

}

PauseState::~PauseState() {

}

void PauseState::init() {
    context->assets->addTexture(PAUSE, "../assets/textures/b2.png");
    pauseBackground.setTexture(context->assets->getTexture(PAUSE));  // присваиваем текстурку нашему фону
    pauseBackground.scale({1.17, 1.1});
    pauseBackground.setColor(sf::Color(255, 255, 255, 170));
    context->window->draw(pauseBackground);


    context->assets->addFont(MAIN_FONT, "../assets/fonts/ARCADECLASSIC.TTF");  //добавляем шрифт
    pauseText.setFont(context->assets->getFont(MAIN_FONT));  // применяем шрифт к тексту
    pauseText.setFillColor(sf::Color::Black);
    pauseText.setOutlineThickness(0.5);
    pauseText.setOutlineColor(sf::Color::White);
    pauseText.setString("game is paused");  // добавляем в текст нашу строку


    pauseText.setOrigin(pauseText.getLocalBounds().width / 2,
                        pauseText.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    pauseText.setPosition(context->window->getSize().x / 2,
                          context->window->getSize().y / 3);  // центрируем текст
}

void PauseState::processStuff() {
    sf::Event event;  // про ивенты почитайте
    while (context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {  // если на крестик нажали
            context->window->close();
        }
        if (event.type == sf::Event::KeyPressed) {  // если кнопку нажали
            switch (event.key.code) {
                case sf::Keyboard::Escape:  // если нажали ескейп то вышли из паузы
                    context->states->popCurrent();
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

void PauseState::update(sf::Time deltaT) {

}

void PauseState::draw() {
//    context->window->clear(sf::Color(255,255,255,128));  // чищу окно
    context->window->draw(pauseText);  // рисую текст
    context->window->display();  // отображаю все что нарисовал
}
