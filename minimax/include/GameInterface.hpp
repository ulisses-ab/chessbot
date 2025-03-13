#include "GameState.hpp"
#include "Evaluator.hpp"
#include "StateManager.hpp"
#include <vector>

#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

class GameInterface {
public:
    GameInterface(Evaluator* evaluator, StateManager* moveGenerator);
    virtual ~GameInterface();

    double evaluateState(GameState* state);
    bool isTerminalState(GameState* state);
    std::vector<GameState*>* generatePossibleNextStates(GameState* state);
    GameState* getEmptyState();
private:
    Evaluator* evaluator;
    StateManager* stateManager;
};

#endif