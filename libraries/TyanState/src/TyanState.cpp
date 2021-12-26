#include "TyanState.hpp"

TyanState::TyanState(std::shared_ptr<GameContext> &context) : context(context) {

    guardian = std::make_unique<Guardian>();
    tyan = std::make_unique<Tyan>();
}

TyanState::~TyanState() {

}

void TyanState::init_win() {
    win.setFont(context->assets->getFont(AssetID::MAIN_FONT));  // применяем шрифт к тексту
    win.setFillColor(sf::Color::Black);
    win.setOutlineThickness(0.5);
    win.setOutlineColor(sf::Color::White);
    
    win.setString("Right");  // добавляем в текст нашу строку
    win.setCharacterSize(100);
    win.setOrigin(question.getLocalBounds().width / 2,
                        question.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    win.setPosition(context->window->getSize().x / 2 - 100,
                          context->window->getSize().y / 3);  // центрируем текст

}

void TyanState::init_question() {
    question.setFont(context->assets->getFont(AssetID::MAIN_FONT));  // применяем шрифт к тексту
    question.setFillColor(sf::Color::Black);
    question.setOutlineThickness(0.5);
    question.setOutlineColor(sf::Color::White);
    
    question.setString("Choose spell");  // добавляем в текст нашу строку
    question.setCharacterSize(80);
    question.setOrigin(question.getLocalBounds().width / 2,
                        question.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    question.setPosition(context->window->getSize().x / 2,
                          context->window->getSize().y / 3); 
}

void TyanState::init_main() {
    choose_str.setFont(context->assets->getFont(AssetID::MAIN_FONT));  // применяем шрифт к тексту
    choose_str.setFillColor(sf::Color::Black);
    choose_str.setOutlineThickness(0.5);
    choose_str.setOutlineColor(sf::Color::White);
    
    choose_str.setString("Choose spell");  // добавляем в текст нашу строку
    choose_str.setCharacterSize(80);
    choose_str.setOrigin(choose_str.getLocalBounds().width / 2,
                        choose_str.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    choose_str.setPosition(context->window->getSize().x / 2,
                          context->window->getSize().y / 3); 
}


void TyanState::init() {
    gaming = true;
    context->assets->addTexture(AssetID::BACKGROUND, "background.png", true);
    context->assets->addTexture(AssetID::TYAN, "tyan.png");
    context->assets->addTexture(AssetID::GUARDIAN, "guardian1.png");
    context->assets->addTexture(AssetID::BULLET, "fireball.png");
    context->assets->addTexture(AssetID::STONE, "stone.png");

    
    context->assets->addTexture(AssetID::PAUSE, "b2.png");
    
    pauseBackground.setTexture(context->assets->getTexture(AssetID::PAUSE));
    pauseBackground.scale({1.17, 1.1});
    pauseBackground.setColor(sf::Color(255, 255, 255, 170));
    
    context->window->draw(pauseBackground);
    context->assets->addFont(AssetID::MAIN_FONT, "ARCADECLASSIC.TTF");  

    background.setTexture(context->assets->getTexture(AssetID::BACKGROUND));  // присваиваем текстурку нашему фону
    background.setTextureRect(context->window->getViewport(context->window->getDefaultView()));  // задаем границы
    timeQuestion.setFont(context->assets->getFont(AssetID::MAIN_FONT));  // применяем шрифт к тексту
    timeQuestion.setFillColor(sf::Color::Black);
    timeQuestion.setOutlineThickness(0.5);
    timeQuestion.setOutlineColor(sf::Color::White);
    
    timeQuestion.setString("Choose spell");  // добавляем в текст нашу строку
    timeQuestion.setCharacterSize(30);
    timeQuestion.setOrigin(choose_str.getLocalBounds().width / 2,
                        choose_str.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    timeQuestion.setPosition(900,
                          60); 
    //присваивем персонажам текстурки и ставим их в нужное место

    tyan->init(&context->assets->getTexture(AssetID::TYAN),
              sf::Vector2f(context->window->getSize().x / 2 + context->assets->getTexture(AssetID::TYAN).getSize().x / 2,
                           context->window->getSize().y / 2));

    guardian->init(&context->assets->getTexture(AssetID::GUARDIAN),
                  sf::Vector2f(context->window->getSize().x / 2 - context->assets->getTexture(AssetID::GUARDIAN).getSize().x / 2,
                               context->window->getSize().y / 2 - (context->assets->getTexture(AssetID::GUARDIAN).getSize().y -
                                                                   context->assets->getTexture(AssetID::TYAN).getSize().y) *
                                                                  0.5));


    init_win();
    init_question();
    init_main();
    timer = 550;
    f_spell.create(120,50, 830,5, "Fire rate");
    f_spell.set_text_size(20);
    s_spell.create(120,50, 955,5, "Immortality");
    s_spell.set_text_size(20);
    th_spell.create(120,50, 1080,5, "Fire backwards");
    th_spell.set_text_size(20);
    back.create(200,40,context->window->getSize().x / 2 - 100, context->window->getSize().y / 2 + 200, "back");
}



void TyanState::task() {
    gaming = false;
    answering = true;
    std::string first_answer, second_answer, third_answer, question_text;
    int answer;
    generate_question(question_text, first_answer, second_answer, third_answer, answer);
    question.setString(question_text);  // добавляем в текст нашу строку
    question.setOrigin(question.getLocalBounds().width / 2,
                        question.getLocalBounds().height / 2);  // ставим точку отсчета в центр текста

    question.setPosition(context->window->getSize().x / 2,
                          context->window->getSize().y / 3); 
    f_answer.create(100,50, 500,600, first_answer);
    s_answer.create(100,50, 300,600, second_answer);
    t_answer.create(100,50, 700,600, third_answer);
    f_answer.set_text_size(20);
    s_answer.set_text_size(20);
    t_answer.set_text_size(20);
    std::cout << answer;
    switch (answer){
        case 1:
            f_answer.is_answer = true;
            break;
        case 2:
            s_answer.is_answer = true;
            break;
        case 3:
            t_answer.is_answer = true;
            break;
        default:
            f_answer.is_answer = true;
            s_answer.is_answer = true;
            t_answer.is_answer = true;
    }
}

void TyanState::colide_menu(sf::Event event) {
    f_spell.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
    s_spell.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
    th_spell.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
}

void TyanState::colide_question(sf::Event event) {
    f_answer.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
    s_answer.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
    t_answer.collidepoint(context->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,event.mouseMove.y)));
}

void TyanState::updateKeyBinds() {
    sf::Event event;  // про ивенты почитайте
    while (context->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {  // если на крестик нажали
            context->window->close();
        }
        if (event.type == sf::Event::KeyPressed) {  // если кнопку нажали
            switch (event.key.code) {
                case sf::Keyboard::Tilde:  // если тильда то закрываемся
                    context->window->close();
                    break;
                default:
                    break;
            }
        }
        else if(event.type == sf::Event::MouseMoved){
                    if (gaming && timer > 600 ||  timer < 20)
                        colide_menu(event);
                    if (answering || timer < 20)
                        colide_question(event);
                    if (answered || timer < 20)
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
                    buff = 3;
                    task();
                }
                if (s_spell.is_hovering) {
                    buff = 4;
                    task();
                }
                if (th_spell.is_hovering) {
                    buff = 5;
                    task();
                }
            }
            if (answered) {
                if (back.is_hovering) {
                    gaming = true;
                    answered = false;
                    timer = 0;
                }
            }
        }
    }
}

void TyanState::right_answer() {
    answered = true;
    answering = false;
    f_answer.is_answer = false;
    s_answer.is_answer = false;
    t_answer.is_answer = false;
    win.setString("Right"); 
    std::cout<<answered;
    player_tyan.send_msg_to_guard(1,buff);
}

void TyanState::wrong_answer() {
    answered = true;
    answering = false;
    f_answer.is_answer = false;
    s_answer.is_answer = false;
    t_answer.is_answer = false;
    win.setString("Lose");
    //player_tyan.send_msg("T0 2 2");
}

void TyanState::processStuff() {
    score++;
}

void TyanState::update(sf::Time deltaT) {
    timer++;
    timer_2++;
}

int flag_tyan = 0;

void TyanState::draw() {
    context->window->clear();
//    player_tyan.send_msg("T0 2 0");
    player_tyan.send_msg_to_guard(1,1);
//    if (player_tyan.recv_msg() == "1")
//    {
//        context->window->clear();
//        context->states->add(std::make_unique<LostState>(context, 2), true);  // todo 2
//    }
    
    if (gaming) {
        context->window->clear();
        context->window->draw(background);
        if (flag_tyan > 1)
        {
            data_msg_guard recv_msg = recv_msg_from_guard();
            flag_tyan = 0;
            bulletsVec.clear();
            stonesVec.clear();
            if (timer_2 > 200) {
                for (int i = 0; i < recv_msg.bullets_y.size(); i++){
                    auto new_bullet = new Bullet({recv_msg.bullets_x[i], recv_msg.bullets_y[i]}, {recv_msg.bullets_dir_x[i], recv_msg.bullets_dir_y[i]});
                    new_bullet->init(&context->assets->getTexture(AssetID::BULLET), new_bullet->getPos());
                    //context->window->draw(*new_bullet);
                    bulletsVec.push_back(new_bullet);
                }
                for (int i = 0; i < recv_msg.stones_y.size(); i++){
                    auto new_stone = new Stone(recv_msg.stones_x[i], recv_msg.stones_y[i], 0);
                    new_stone->init(&context->assets->getTexture(AssetID::STONE), new_stone->getPos());
                    //context->window->draw(*new_bullet);
                    stonesVec.push_back(new_stone);
                }
            }
            if (recv_msg.buff == 6){
            context->window->clear();
            context->states->add(std::make_unique<LostState>(context, score), true);
            }
        }
        flag_tyan++;
        if (timer < 600) 
            timeQuestion.setString("task cd " + std::to_string(10 - timer/60));
        else 
            timeQuestion.setString("task ready");
        sf::RectangleShape rectangle(sf::Vector2f(660.f, 60.f));
        rectangle.move(828, 0); // перемещаем его в нижний ряд справа от многоугольника
        rectangle.setFillColor(sf::Color(175, 180, 240)); // устанавливаем цвет прямоугольника
        context->window->draw(rectangle);
        context->window->draw(*tyan);
        context->window->draw(*guardian);
        context->window->draw(timeQuestion);  // рисую текст
        f_spell.draw(context);
        s_spell.draw(context);
        th_spell.draw(context);
    }
    for (auto & bullet : bulletsVec) {
            context->window->draw(*bullet);
        }
    for (auto & stone : stonesVec) {
            context->window->draw(*stone);
    }
    if (answering)
    {
        context->window->clear();
        context->window->draw(question);
        f_answer.draw(context);
        s_answer.draw(context);
        t_answer.draw(context);
        
    }
    if (answered)
    {
        context->window->clear();
        back.draw(context);
        context->window->draw(win);
    }
    
    context->window->display();  // отображаю все что нарисовал
}

void TyanState::resume() {
    context->states->popCurrent();
}
