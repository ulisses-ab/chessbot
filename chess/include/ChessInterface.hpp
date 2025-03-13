#include "../../minimax/include/GameInterface.hpp"
#include "ChessEvaluator.hpp"
#include "ChessStateManager.hpp"
#include <vector>

#ifndef CHESSEINTERFACE_H
#define CHESSEINTERFACE_H

class ChessInterface : public GameInterface {
public:
    double evaluateState(GameState* state);
    std::vector<GameState*>* generatePossibleNextStates(GameState* state);
    GameState* getEmptyState();
private:
    ChessState* cast(GameState* state);;
};

#endif