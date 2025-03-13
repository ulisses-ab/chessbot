#include "GameState.hpp"
#include <vector>

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

class StateManager {
public:
    StateManager();

    virtual std::vector<GameState*>* generatePossibleNextStates(GameState* state) = 0;
    virtual bool isTerminalState(GameState* state) = 0;
    virtual GameState* getEmptyState() = 0;
};

#endif