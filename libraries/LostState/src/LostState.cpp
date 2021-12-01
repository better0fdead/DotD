#include "LostState.hpp"

LostState::LostState(std::shared_ptr<GameContext> &context) : context(context) {

}

LostState::~LostState() {

}

void LostState::init() {
    context->assets->addTexture(LOST, "../assets/textures/b2.png");
    lostBackground.setTexture(context->assets->getTexture(LOST));  // присваиваем текстурку нашему фону
    lostBackground.scale({1.17, 1.1});


    context->assets->addFont(MAIN_FONT, "../assets/fonts/ARCADECLASSIC.TTF");  //добавляем шрифт
    lostText.setFont(context->assets->getFont(MAIN_FONT));  // применяем шрифт к тексту
    lostText.setFillColor(sf::Color::Black);
    lostText.setOutlineThickness(0.5);
    lostText.setLetterSpacing(2.5);
    lostText.setOutlineColor(sf::Color::White);
    lostText.setString(
            "YOU  LOST\npress enter to play again\npress esc to go to menu");  // добавляем в текст нашу строку



    lostText.setOrigin(lostText.getLocalBounds().width / 2,
                       lostText.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    lostText.setPosition(context->window->getSize().x / 2,
                         context->window->getSize().y / 2);  // центрируем текст
}

void LostState::updateKeyBinds() {
    sf::Event event;  // про ивенты почитайте
    while (context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {  // если на крестик нажали
            context->window->close();
        }
        if (event.type == sf::Event::KeyPressed) {  // если кнопку нажали
            switch (event.key.code) {
                case sf::Keyboard::Escape:  // если нажали ескейп то в меню
                    context->states->add(std::make_unique<MenuState>(context), true);
                    break;
                case sf::Keyboard::Return:  // если ентре то заново
                    context->states->add(std::make_unique<GameState>(context), true);
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


void LostState::processStuff() {

}

void LostState::update(sf::Time deltaT) {

}

void LostState::draw() {
    context->window->clear();
    context->window->draw(lostBackground);
    context->window->draw(lostText);  // рисую текст
    context->window->display();  // отображаю все что нарисовал
}

