#include "GameState.hpp"
#include "Evaluator.hpp"
#include "StateManager.hpp"
#include <vector>

#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

class GameInterface {
public:
    GameInterface(Evaluator* evaluator, StateManager* moveGenerator);

    double evaluateState(GameState* state);
    bool isTerminalState(GameState* state);
    std::vector<GameState*>* generatePossibleNextStates(GameState* state);
private:
    Evaluator* evaluator;
    StateManager* StateManager;
};

#endif