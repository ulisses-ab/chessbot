#include "../include/GameInterface.hpp"

GameInterface::GameInterface(Evaluator* evaluator, StateManager* stateManager) {
    this->evaluator = evaluator;
    this->stateManager = stateManager;
}

GameInterface::~GameInterface() {
    delete this->evaluator, this->stateManager;
}

double GameInterface::evaluateState(GameState* state) {
    return this->evaluator->evaluateState(state);
}

bool GameInterface::isTerminalState(GameState* state) {
    return this->stateManager->isTerminalState(state);
}

std::vector<GameState*>* GameInterface::generatePossibleNextStates(GameState* state) {
    return this->stateManager->generatePossibleNextStates(state);
}

GameState* GameInterface::getEmptyState() {
    return this->stateManager->getEmptyState();
}