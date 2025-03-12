#include "include/Minimax.hpp"
#include <vector>
#include <float.h>

const double Minimax::NAN = DBL_MAX;
const double Minimax::INF = DBL_MAX / 2;

Minimax::Minimax(GameInterface* gameInterface) {
    this->gameInterface = gameInterface;
}

GameState* Minimax::max(GameState* gameState, int depth) {
    return this->max(gameState, depth, NAN, NAN);
}

GameState* Minimax::min(GameState* gameState, int depth) {
    return this->min(gameState, depth, NAN, NAN);
}

GameState* Minimax::max(GameState* gameState, int depth, double alpha, double beta) {
    
    std::vector<GameState*> possibleNextStates = this->gameInterface->generatePossibleNextStates(gameState);

    for(auto possibleNextState : possibleNextStates) {

    }
}

GameState* Minimax::min(GameState* gameState, int depth, double alpha, double beta) {

}
