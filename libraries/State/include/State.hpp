#pragma once

#include <SFML/Graphics.hpp>


class State {
public:
    State() {};

    virtual ~State() {};


    virtual void init() = 0;  // инициализируем состояние и объекты в нем
    virtual void updateKeyBinds() = 0;  // чекаем кнопки и евенты
    virtual void processStuff() = 0;  // проверяем различные состояния объектов(коллизии и тп)
    virtual void update(sf::Time deltaT) = 0; // обновляем данные
    virtual void draw() = 0;  // рисуем

};
