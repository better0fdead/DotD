#include "TyanState.hpp"

TyanState::TyanState(std::shared_ptr<GameContext> &context) : context(context) {

}

TyanState::~TyanState() {

}

void TyanState::init() {
    context->assets->addTexture(PAUSE, "../assets/textures/b2.png");
    pauseBackground.setTexture(context->assets->getTexture(PAUSE));  // присваиваем текстурку нашему фону
    pauseBackground.scale({1.17, 1.1});
    pauseBackground.setColor(sf::Color(255, 255, 255, 170));
    context->window->draw(pauseBackground);


    context->assets->addFont(MAIN_FONT, "../assets/fonts/ARCADECLASSIC.TTF");  //добавляем шрифт

    win.setFont(context->assets->getFont(MAIN_FONT));  // применяем шрифт к тексту
    win.setFillColor(sf::Color::Black);
    win.setOutlineThickness(0.5);
    win.setOutlineColor(sf::Color::White);
    
    win.setString("Right");  // добавляем в текст нашу строку
    win.setCharacterSize(100);
    win.setOrigin(question.getLocalBounds().width / 2,
                        question.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    win.setPosition(context->window->getSize().x / 2,
                          context->window->getSize().y / 3);  // центрируем текст

    lose.setFont(context->assets->getFont(MAIN_FONT));  // применяем шрифт к тексту
    lose.setFillColor(sf::Color::Black);
    lose.setOutlineThickness(0.5);
    lose.setOutlineColor(sf::Color::White);
    
    lose.setString("Wrong");  // добавляем в текст нашу строку
    lose.setCharacterSize(100);
    lose.setOrigin(question.getLocalBounds().width / 2,
                        question.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    lose.setPosition(context->window->getSize().x / 2,
                          context->window->getSize().y / 3);  // центрируем текст
    task();

    
}


void TyanState::task() {

    question.setFont(context->assets->getFont(MAIN_FONT));  // применяем шрифт к тексту
    question.setFillColor(sf::Color::Black);
    question.setOutlineThickness(0.5);
    question.setOutlineColor(sf::Color::White);
    
    question.setString("7 + 2 / 2");  // добавляем в текст нашу строку
    question.setCharacterSize(100);
    question.setOrigin(question.getLocalBounds().width / 2,
                        question.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    question.setPosition(context->window->getSize().x / 2,
                          context->window->getSize().y / 3);  // центрируем текст
    f_answer.create(50,50, 550,600, "8");
    f_answer.is_answer = true;
    s_answer.create(50,50, 450,600, "7");
    t_answer.create(50,50, 650,600, "6");

}

void TyanState::updateKeyBinds() {
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
        else if(event.type == sf::Event::MouseMoved){
                    f_answer.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
                    s_answer.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
                    t_answer.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
                }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if (f_answer.is_hovering)
            {
                if (f_answer.is_answer) {
                    right_answer();
                }
                else {
                    wrong_answer();
                }
            }
            else if (s_answer.is_hovering)
            {
                if (s_answer.is_answer) {
                    right_answer();
                }
                else {
                    wrong_answer();
                }
            }
            else if (t_answer.is_hovering)
            {
                if (t_answer.is_answer) {
                    right_answer();
                }
                else {
                    wrong_answer();
                }
            }
        }
    }
}

void TyanState::right_answer() {
    answered = true;
    question.setString("Win");
}

void TyanState::wrong_answer() {
    answered = true;
    question.setString("Lose");
}

void TyanState::processStuff() {

}

void TyanState::update(sf::Time deltaT) {

}

void TyanState::draw() {
    context->window->clear();
    context->window->draw(question);  // рисую текст
    if (!answered) {
        f_answer.draw(context);
        s_answer.draw(context);
        t_answer.draw(context);
    }
    context->window->display();  // отображаю все что нарисовал
}

void TyanState::resume() {
    context->states->popCurrent();
}
