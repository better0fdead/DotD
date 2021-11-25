#pragma once

#include "State.hpp"
#include "stack"
#include "memory"

class StateManager {
public:
    StateManager();

    ~StateManager();

    void add(std::unique_ptr<State> toAdd, bool replace = false);

    void popCurrent();

    void switchStateIfNeeded();

    std::unique_ptr<State> &getCurrentState();

private:
    std::stack<std::unique_ptr<State>> statesStack;
    std::unique_ptr<State> newState;

    bool needToAdd;
    bool needToRemove;
    bool needToReplace;

};