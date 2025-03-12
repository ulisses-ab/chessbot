#include "GameState.hpp"
#include "Evaluator.hpp"
#include "StateGenerator.hpp"
#include <vector>

#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

class GameInterface {
public:
    GameInterface(Evaluator* evaluator, StateGenerator* moveGenerator);

    double evaluate(GameState* GameState);
    std::vector<GameState*> generatePossibleNextStates(GameState* gameState);
};

#endif