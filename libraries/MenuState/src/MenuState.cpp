#include "MenuState.hpp"
#include "GameState.hpp"

MenuState::MenuState(std::shared_ptr<GameContext> &context) : context(context) {

}

MenuState::~MenuState() {

}

void MenuState::init() {
    context->assets->addTexture(MENU, "../assets/textures/menubackground_extrashakal.jpg");
    menuBackground.setTexture(context->assets->getTexture(MENU));  // присваиваем текстурку нашему фону

    context->assets->addFont(MAIN_FONT, "../assets/fonts/ARCADECLASSIC.TTF");  //добавляем шрифт
    playText.setFont(context->assets->getFont(MAIN_FONT));  // применяем шрифт к тексту
    playText.setString("work please");  // добавляем в текст нашу строку

    playText.setOrigin(playText.getLocalBounds().width / 2,
                       playText.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    playText.setPosition(context->window->getSize().x / 2,
                         context->window->getSize().y / 2);  // центрируем текст
}

void MenuState::update(sf::Time deltaT) {

}

void MenuState::draw() {
    context->window->clear();  // чищу окно
    context->window->draw(menuBackground);
    context->window->draw(playText);  // рисую текст
    context->window->display();  // отображаю все что нарисовал
}

void MenuState::processStuff() {
    sf::Event event;  // про ивенты почитайте
    while (context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {  // если на крестик нажали
            context->window->close();
        }
        if (event.type == sf::Event::KeyPressed) {  // если кнопку нажали
            switch (event.key.code) {
                case sf::Keyboard::Return:  // если нажали Enter то перешли в игровое состояние
                    // todo а надо сделать в коннектинг
                    context->states->add(std::make_unique<GameState>(context), true);
                    break;
                case sf::Keyboard::Escape:  // если ескейп то закрываемся
                    context->window->close();
                    break;
                default:
                    break;
            }
        }
    }
}
