#pragma once

#include <SFML/Graphics.hpp>


class State {
public:
    State() {};

    virtual ~State() {};


    virtual void init() = 0;  // инициализируем состояние и объекты в нем
    virtual void processStuff() = 0;  //чекаем кнопки и евенты
    virtual void update(sf::Time deltaT) = 0; // обновляем данные
    virtual void draw() = 0;  // рисуем

    // эти два не чисто виртуальные потому что не все состояния надо паузить и возобновлять
    virtual void pause() {};
    virtual void start() {};

};
