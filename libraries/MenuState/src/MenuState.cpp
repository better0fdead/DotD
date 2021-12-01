#include "MenuState.hpp"

MenuState::MenuState(std::shared_ptr<GameContext> &context) : context(context) {

}

MenuState::~MenuState() {

}

void MenuState::init() {
    context->assets->addTexture(MENU, "../assets/textures/menubackground_extrashakal.jpg");
    menuBackground.setTexture(context->assets->getTexture(MENU));  // присваиваем текстурку нашему фону
    music.openFromFile("../assets/music/theme.wav");
    music.play();
    context->assets->addFont(MAIN_FONT, "../assets/fonts/ARCADECLASSIC.TTF");  //добавляем шрифт
    playText.setFont(context->assets->getFont(MAIN_FONT));  // применяем шрифт к тексту
    playText.setString("work please");  // добавляем в текст нашу строку

    playText.setOrigin(playText.getLocalBounds().width / 2,
                       playText.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    playText.setPosition(context->window->getSize().x / 2,
                         context->window->getSize().y / 2);  // центрируем текст

    exit_button.create(100,20, 10,10, "exit");
    mute_button.create(100,20,1000,700,"mute");
    play_button.create(200,40,context->window->getSize().x / 2 - 100, context->window->getSize().y / 2 + 200, "play");
}

void MenuState::updateKeyBinds() {
    sf::Event event;  // про ивенты почитайте
    while (context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {  // если на крестик нажали
            context->window->close();
        }
        else if (event.type == sf::Event::KeyPressed) {  // если кнопку нажали
            switch (event.key.code) {
                case sf::Keyboard::Return:  // если нажали Enter то перешли в игровое состояние
                    // todo а надо сделать в коннектинг
                    context->window->clear();  // чищу окно
                    context->states->add(std::make_unique<GameState>(context), true);
                    break;
                case sf::Keyboard::Escape:  // если ескейп то закрываемся
                    context->window->close();
                    break;
                default:
                    break;
            }
        }
        else if(event.type == sf::Event::MouseMoved){
                    play_button.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
                    mute_button.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
                    exit_button.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
                }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if (exit_button.is_hovering)
                context->window->close();
            else if (play_button.is_hovering)
            {
                context->window->clear();  // чищу окно
                context->states->add(std::make_unique<GameState>(context), true);
            }
            else if (mute_button.is_hovering)
            {
                if (mute_button.is_muted == false)
                {
                    music.pause();
                    mute_button.is_muted = true;
                }
                else
                {
                    music.play();
                    mute_button.is_muted = false;
                }
            }
        }
    }
}

void MenuState::processStuff() {

}


void MenuState::update(sf::Time deltaT) {


}

void MenuState::draw() {
    context->window->clear();  // чищу окно
    context->window->draw(menuBackground);
    context->window->draw(playText);  // рисую текст
    //context->window->draw(button.rect);
    exit_button.draw(context);
    play_button.draw(context);
    mute_button.draw(context);
    context->window->display();  // отображаю все что нарисовал
}

