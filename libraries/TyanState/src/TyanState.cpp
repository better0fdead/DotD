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

    win.setPosition(context->window->getSize().x / 2 - 100,
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

    question.setFont(context->assets->getFont(MAIN_FONT));  // применяем шрифт к тексту
    question.setFillColor(sf::Color::Black);
    question.setOutlineThickness(0.5);
    question.setOutlineColor(sf::Color::White);
    
    question.setString("Choose spell");  // добавляем в текст нашу строку
    question.setCharacterSize(80);
    question.setOrigin(question.getLocalBounds().width / 2,
                        question.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    question.setPosition(context->window->getSize().x / 2,
                          context->window->getSize().y / 3); 
    
    f_spell.create(250,50, 500,600, "Fire rate");
    s_spell.create(250,50, 180,600, "Immortality");
    th_spell.create(250,50, 820,600, "Slow stones");
    back.create(200,40,context->window->getSize().x / 2 - 100, context->window->getSize().y / 2 + 200, "back");
    //task();
    
}


void TyanState::task() {
    answering = true;
    question.setString("V kakom gody vyshla brigada");  // добавляем в текст нашу строку
    question.setOrigin(question.getLocalBounds().width / 2,
                        question.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    question.setPosition(context->window->getSize().x / 2,
                          context->window->getSize().y / 3); 
    f_answer.create(100,50, 500,600, "2002");
    f_answer.is_answer = true;
    s_answer.create(100,50, 380,600, "2005");
    t_answer.create(100,50, 620,600, "1997");

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
                    f_spell.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
                    s_spell.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
                    th_spell.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
                    back.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
                }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if (answering)
            {
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
            if (!answering && !answered){
                if (f_spell.is_hovering) {
                    task();
                }
                if (s_spell.is_hovering) {
                    task();
                }
                if (th_spell.is_hovering) {
                    task();
                }
            }
            if (answered) {
                if (back.is_hovering) {
                    answered = false;
                    answering = false;
                }
            }
        }
    }
}

void TyanState::right_answer() {
    answered = true;
    answering = false;
    win.setString("Right"); 

    player_tyan.send_msg("T0 2 3");

}

void TyanState::wrong_answer() {
    answered = true;
    answering = false;

    win.setString("Lose");
    player_tyan.send_msg("T0 2 2");

}

void TyanState::processStuff() {

}

void TyanState::update(sf::Time deltaT) {

}

void TyanState::draw() {
    context->window->clear();

    player_tyan.send_msg("T0 2 0");
    if (player_tyan.recv_msg() == "1")

    {
        context->window->clear();
        context->states->add(std::make_unique<LostState>(context, 2), true);  // todo 2
    }
    
    if (!answering && !answered) {
        context->window->draw(question);  // рисую текст
        f_spell.draw(context);
        s_spell.draw(context);
        th_spell.draw(context);
    }
    else if (answering)
    {
        context->window->draw(question);
        f_answer.draw(context);
        s_answer.draw(context);
        t_answer.draw(context);
        //
        
    }
    else if (answered)
    {
        back.draw(context);
        context->window->draw(win);
    }
    context->window->display();  // отображаю все что нарисовал
}

void TyanState::resume() {
    context->states->popCurrent();
}
