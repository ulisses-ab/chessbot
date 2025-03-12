#include "GameInterface.hpp"
#include "GameState.hpp"

#ifndef MINIMAX_H
#define MINIMAX_H

class Minimax {
public:
    Minimax(GameInterface* gameInterface);
private:
    double max(GameState* state, int depth);
    double min(GameState* state, int depth);
    double max(GameState* state, int depth, double alpha, double beta);
    double min(GameState* state, int depth, double alpha, double beta);
    
    GameInterface* gameInterface;
};

#endif