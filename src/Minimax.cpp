#include "include/Minimax.hpp"
#include <vector>
#include <float.h>

Minimax::Minimax(GameInterface* gameInterface) {
    this->gameInterface = gameInterface;
}

double Minimax::max(GameState* gameState, int depth) {
    return this->max(gameState, depth, -DBL_MAX, DBL_MAX);
}

double Minimax::min(GameState* gameState, int depth) {
    return this->min(gameState, depth, -DBL_MAX, DBL_MAX);
}

double Minimax::max(GameState* gameState, int depth, double alpha, double beta) {
    if(depth == 0) return this->gameInterface->evaluate(gameState);

    std::vector<GameState*> possibleNextStates = this->gameInterface->generatePossibleNextStates(gameState);

    if(possibleNextStates.size() == 0) return this->gameInterface->evaluate(gameState); 

    for(auto possibleNextState : possibleNextStates) {

    }
}

double Minimax::min(GameState* gameState, int depth, double alpha, double beta) {

}
