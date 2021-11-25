#include "MenuState.hpp"

MenuState::MenuState(std::shared_ptr<GameContext> &context) : context(context) {

}

MenuState::~MenuState() {

}

void MenuState::init() {
    context->assets->addFont(MAIN_FONT, "../assets/fonts/ARCADECLASSIC.TTF");
    playText.setFont(context->assets->getFont(MAIN_FONT));
    playText.setString("work please");
}

void MenuState::update() {

}

void MenuState::draw() {
    context->window->clear();
    context->window->draw(playText);
    context->window->display();
}

void MenuState::processStuff() {
    sf::Event event;
    while (context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            context->window->close();

    }
}

void MenuState::updateKeyBinds() {

}

