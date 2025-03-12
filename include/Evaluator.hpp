#include "GameState.hpp"

#ifndef EVALUATOR_H
#define EVALUATOR_H

class Evaluator {
public:
    Evaluator();

    static double evaluate(GameState* gameState);
};

#endif