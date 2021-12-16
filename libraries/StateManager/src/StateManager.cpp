#include <StateManager.hpp>

StateManager::StateManager() : needToAdd(false), needToRemove(false), needToReplace(false) {

}

StateManager::~StateManager() {

}

void StateManager::add(std::unique_ptr<State> toAdd, bool replace) {
    needToAdd = true;
    newState = std::move(toAdd);
    needToReplace = replace;
}

void StateManager::popCurrent() {
    needToRemove = true;
}

void StateManager::switchStateIfNeeded() {
    if (needToRemove && !statesStack.empty()) { // если надо сменить состояние, удалив текущее
        statesStack.pop();
        needToRemove = false;
    }

    if (needToAdd) {  // надо сменить на новое состояние
        if (needToReplace && !statesStack.empty()) {  // если сменить с заменой то попаем
            statesStack.pop();
            needToReplace = false;
        }

        statesStack.push(std::move(newState));  // наконец сменяем
        statesStack.top()->init();
        needToAdd = false;
    }
}

std::unique_ptr<State> &StateManager::getCurrentState() {
    return statesStack.top();
}
