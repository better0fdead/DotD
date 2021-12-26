#include "LoadState.hpp"


LoadState::LoadState(std::shared_ptr<GameContext> &context) : context(context) {

}

LoadState::~LoadState() {

}

void LoadState::init() {
    loadtex.loadFromFile("../assets/textures/loading.jpg");
    menuBackground.setTexture(loadtex);  // присваиваем текстурку нашему фону
    music.openFromFile("../assets/music/theme.wav");
    music.play();
    context->assets->addFont(AssetID::MAIN_FONT, "../assets/fonts/ARCADECLASSIC.TTF");  //добавляем шрифт
    playText.setFont(context->assets->getFont(AssetID::MAIN_FONT));  // применяем шрифт к тексту
    playText.setString("Loading");  // добавляем в текст нашу строку
    playText.setCharacterSize(100);
    playText.setOrigin(playText.getLocalBounds().width / 2,
                       playText.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    playText.setPosition(context->window->getSize().x / 2,
                         context->window->getSize().y / 2 - 100);  // центрируем текст

    exit_button.create(100, 20, 10, 10, "exit");
    mute_button.create(100, 20, 1000, 700, "mute");
    Tyan_button.create(200, 40, context->window->getSize().x / 2 - 200, context->window->getSize().y / 2 + 200, "Tyan");
    Guardian_button.create(200, 40, context->window->getSize().x / 2 + 100, context->window->getSize().y / 2 + 200,
                           "Guardian");
}

void LoadState::updateKeyBinds() {
    sf::Event event;  // про ивенты почитайте
    while (context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {  // если на крестик нажали
            context->window->close();
        } else if (event.type == sf::Event::KeyPressed) {  // если кнопку нажали
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
        } else if (event.type == sf::Event::MouseMoved) {
            play_button.collidepoint(
                    context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
            mute_button.collidepoint(
                    context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
            exit_button.collidepoint(
                    context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
            Tyan_button.collidepoint(
                    context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
            Guardian_button.collidepoint(
                    context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)));
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (exit_button.is_hovering)
                context->window->close();
            else if (play_button.is_hovering) {
                context->window->clear();  // чищу окно
                context->states->add(std::make_unique<GameState>(context), true);
            } else if (mute_button.is_hovering) {
                if (mute_button.is_muted == false) {
                    music.pause();
                    mute_button.is_muted = true;
                } else {
                    music.play();
                    mute_button.is_muted = false;
                }
            } else if (Tyan_button.is_hovering) {
                is_connecting = true;
                role = 2;
                player_tyan.send_msg("T0 1");
            } else if (Guardian_button.is_hovering) {
                role = 1;
                is_connecting = true;
                player_guardian.send_msg("H0 1");
            }
        }
    }
}

void LoadState::processStuff() {

}


void LoadState::update(sf::Time deltaT) {


}

void LoadState::draw() {
    context->window->clear();  // чищу окно
    context->window->draw(menuBackground);
    context->window->draw(playText);  // рисую текст
    //context->window->draw(button.rect);
    exit_button.draw(context);


    if (!is_connecting) {
        Tyan_button.draw(context);
        Guardian_button.draw(context);
    } else {
        std::cout<<"role"<<role<<std::endl;
        if (role == 1) player_guardian.send_msg("H0 7");

        else if (role == 2) player_tyan.send_msg("T0 7");

        if (player_guardian.recv_msg()[0] == '1') {
            if (role == 1) {
                std::cout<<"try Guard"<<std::endl;
                context->states->add(std::make_unique<GameState>(context), true);
            } else if (role == 2) {
                std::cout<<"try tyan"<<std::endl;
                context->states->add(std::make_unique<TyanState>(context), true);
            }
        }
    }
    mute_button.draw(context);
    context->window->display();  // отображаю все что нарисовал
}

