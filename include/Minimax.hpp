#include "GameInterface.hpp"
#include "GameState.hpp"

#ifndef MINIMAX_H
#define MINIMAX_H

class Minimax {
public:
    Minimax(GameInterface* gameInterface);

    GameState* findMaximumNextState(GameState* state, int depth);
    GameState* findMinimumNextState(GameState* state, int depth);
private:
    double max(GameState* state, int depth, double alpha, double beta);
    double min(GameState* state, int depth, double alpha, double beta);
    double max(GameState* state, int depth, double alpha, double beta, GameState* bestState);
    double min(GameState* state, int depth, double alpha, double beta, GameState* bestState);
    double evaluateNextStates(GameState* state, int depth, double alpha, double beta, bool isMaximizing);

    double evaluateState(GameState* state);
    bool isTerminalState(GameState* state);
    std::vector<GameState*>* generatePossibleNextStates(GameState* state);
    void deleteStateVector(std::vector<GameState*>* stateVector);
    
    GameInterface* gameInterface;
};

#endif