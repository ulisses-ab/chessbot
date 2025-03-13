#include "../../minimax/include/Evaluator.hpp"

#ifndef CHESSEVALUATOR_H
#define CHESSEVALUATOR_H

class ChessEvaluator : public Evaluator {
public:
    double evaluateState(GameState* state);
};

#endif