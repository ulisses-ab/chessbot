#include "GameState.hpp"

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

class StateManager {
public:
    StateManager();

    virtual std::vector<GameState*>* generatePossibleNextStates(GameState* state) = 0;
    virtual double isTerminalState(GameState* state) = 0;
};

#endif