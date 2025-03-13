#include "GameState.hpp"
#include <vector>

#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

class GameInterface {
public:
    virtual double evaluateState(GameState* state) = 0;
    virtual std::vector<GameState*>* generatePossibleNextStates(GameState* state) = 0;
    virtual GameState* getEmptyState() = 0;
};

#endif