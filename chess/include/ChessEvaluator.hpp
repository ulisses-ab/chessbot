#include "ChessState.hpp"

#ifndef CHESSEVALUATOR_H
#define CHESSEVALUATOR_H

class ChessEvaluator {
public:
    double evaluateState(GameState* state);
};

#endif