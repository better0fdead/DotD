#pragma once

#include "State.hpp"
#include "stack"
#include "memory"

class StateManager {
public:
    StateManager();

    ~StateManager();

    void add(std::unique_ptr<State> toAdd, bool replace = false);  //добавить новое состояние

    void popCurrent();  // удалить текущее состояние

    void switchStateIfNeeded();  // сменить состояние определенным образом

    std::unique_ptr<State> &getCurrentState();  // получить текущее сост

private:
    std::stack<std::unique_ptr<State>> statesStack;  // все состояния хранятся тута
    std::unique_ptr<State> newState;  // промежутачное место куда кладем состояние прежде чем переключиться на него

    bool needToAdd;  //надо добавлять удалять или заменять
    bool needToRemove;
    bool needToReplace;
};