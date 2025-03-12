#include "GameState.hpp"

#ifndef STATEGENERATOR_H
#define STATEGENERATOR_H

class StateGenerator {
public:
    StateGenerator();

    virtual double generatePossibleNextStates(GameState gameState) = 0;
};

#endif