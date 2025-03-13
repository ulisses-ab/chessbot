#include "../include/Minimax.hpp"
#include <vector>
#include <float.h>
#include <algorithm>
#include <stdexcept>

Minimax::Minimax(GameInterface* gameInterface) {
    this->gameInterface = gameInterface;
}

Minimax::~Minimax() {
    delete this->gameInterface;
}

GameState* Minimax::findMaximumNextState(GameState* state, int depth) {
    GameState* bestState = this->gameInterface->getEmptyState();
    this->max(state, depth, -DBL_MAX, DBL_MAX, bestState);
    return bestState;
}

GameState* Minimax::findMinimumNextState(GameState* state, int depth) {
    GameState* bestState = this->gameInterface->getEmptyState();
    this->min(state, depth, -DBL_MAX, DBL_MAX, bestState);
    return bestState;
}

double Minimax::max(GameState* state, int depth, double alpha, double beta) {
    return this->max(state, depth, alpha, beta, nullptr);
}

double Minimax::min(GameState* state, int depth, double alpha, double beta) {
    return this->min(state, depth, alpha, beta, nullptr);
}

double Minimax::max(GameState* state, int depth, double alpha, double beta, GameState* bestState) {
    if (depth == 0 || this->isTerminalState(state)) {
        return this->evaluateState(state);
    }

    std::vector<GameState*>* possibleNextStates = this->generatePossibleNextStates(state);
    double maxEvaluation = -DBL_MAX;
    GameState* maxState;

    for (auto nextState : *possibleNextStates) {
        double evaluation = this->min(nextState, depth - 1, alpha, beta);
        if(evaluation > maxEvaluation) {
            maxEvaluation = evaluation;
            maxState = nextState;
        }
        if (maxEvaluation >= beta) {
            break;
        }
        alpha = std::max(alpha, maxEvaluation);
    }
    
    if(bestState != nullptr) {
        *bestState = *maxState;
    }

    this->deleteStateVector(possibleNextStates);
    return maxEvaluation;
}

double Minimax::min(GameState* gameState, int depth, double alpha, double beta, GameState* bestState) {
    if (depth == 0 || this->isTerminalState(gameState)) {
        return this->evaluateState(gameState);
    }

    std::vector<GameState*>* possibleNextStates = this->gameInterface->generatePossibleNextStates(gameState);
    double minEvaluation = DBL_MAX;
    GameState* minState;

    for (auto nextState : *possibleNextStates) {
        double evaluation = this->max(nextState, depth - 1, alpha, beta);
        if(evaluation < minEvaluation) {
            minEvaluation = evaluation;
            minState = nextState;
        }
        if (minEvaluation <= alpha) {
            break;
        }
        beta = std::min(beta, minEvaluation);
    }
    
    if(bestState != nullptr) {
        *bestState = *minState;
    }

    this->deleteStateVector(possibleNextStates);
    return minEvaluation;
}

std::vector<GameState*>* Minimax::generatePossibleNextStates(GameState* state) {
    return this->gameInterface->generatePossibleNextStates(state);
}

bool Minimax::isTerminalState(GameState* state) {
    return this->gameInterface->isTerminalState(state);
}

double Minimax::evaluateState(GameState* state) {
    return this->gameInterface->evaluateState(state);
}

void Minimax::deleteStateVector(std::vector<GameState*>* stateVector) {
    for(auto state : *stateVector) {
        delete state;
    }

    delete stateVector;
}