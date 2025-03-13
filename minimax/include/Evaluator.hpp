#include "GameState.hpp"

#ifndef EVALUATOR_H
#define EVALUATOR_H

class Evaluator {
public:
    virtual double evaluateState(GameState* state) = 0;
};

#endif