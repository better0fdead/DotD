#include <StateManager.hpp>
#include <iostream>

StateManager::StateManager() : needToAdd(false), needToRemove(false), needToReplace(false) {

}

StateManager::~StateManager() {

}


void StateManager::add(std::unique_ptr<State> toAdd, bool replace) {
    needToAdd = true;
    newState = std::move(toAdd);
//    newState->init();
    needToReplace = replace;
}

void StateManager::popCurrent() {
    needToRemove = true;
}

void StateManager::switchStateIfNeeded() {
    if (needToRemove && !statesStack.empty()) { // если надо сменить состояние, удалив текущее
        statesStack.pop();
//        if (!statesStack.empty()) {
//            statesStack.top()->start();  // запуск следующего состояния
//        }
        needToRemove = false;
    }

    if (needToAdd) {  // надо сменить на новое состояние
        if (needToReplace && !statesStack.empty()) {  // если сменить с заменой то попаем
            statesStack.pop();
            needToReplace = false;
        }

//        if(!statesStack.empty()){  // если было состояние до нового, то его на паузу ставим
//            statesStack.top()->pause();
//        }

        statesStack.push(std::move(newState));  // наконец сменяем
        statesStack.top()->init();
        needToAdd = false;
    }
    std::cout << statesStack.size()<< std::endl;

}

std::unique_ptr<State> &StateManager::getCurrentState() {
    return statesStack.top();
}


