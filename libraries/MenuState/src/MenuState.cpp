#include "MenuState.hpp"

MenuState::MenuState(std::shared_ptr<GameContext> &context) : context(context) {

}

MenuState::~MenuState() {

}

void MenuState::init() {
    context->assets->addTexture(AssetID::MENU, "menubackground_extrashakal.jpg");
    menuBackground.setTexture(context->assets->getTexture(AssetID::MENU));  // присваиваем текстурку нашему фону

    music.openFromFile("../assets/music/theme.wav");
    music.play();

    context->assets->addFont(AssetID::MAIN_FONT, "ARCADECLASSIC.TTF");  //добавляем шрифт
    playText.setFont(context->assets->getFont(AssetID::MAIN_FONT));  // применяем шрифт к тексту
    playText.setString("work please");  // добавляем в текст нашу строку

    playText.setOrigin(playText.getLocalBounds().width / 2,
                       playText.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    playText.setPosition(context->window->getSize().x / 2,
                         context->window->getSize().y / 2);  // центрируем текст

    exit_button.create(100,20, 10,10, "exit");  //todo цифры в дефайны или по умолчанию сделай кнопу поределенного размера
    mute_button.create(100,20,1000,700,"mute");
    play_button.create(200,40,context->window->getSize().x / 2 - 100, context->window->getSize().y / 2 + 200, "play");
}

void MenuState::updateKeyBinds() {
    sf::Event event;  // про ивенты почитайте
    while (context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {  // если на крестик нажали
            context->window->close();
        }
        if (event.type == sf::Event::KeyPressed) {  // если кнопку нажали
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
                context->states->add(std::make_unique<LoadState>(context), true);
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
    exit_button.draw(context);  // todo ЧТО ЭТО ЗА ХУЙНЯ почему у тебя дров отдельный И ПОЧЕМУ ОН КОНТЕКСТ ПРИНИМАЕТ
    play_button.draw(context);  // todo поправь сделай чтобы наш дефолтный дров на влю игру который работает и на твою конпу каботал
    mute_button.draw(context);  // todo у тебя кнопка должна наследоваться от сущности которую я создал это на юмл было........ федя меняй!!!!
    context->window->display();  // отображаю все что нарисовал
}
