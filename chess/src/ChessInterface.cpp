#include "../include/ChessInterface.hpp"
#include "../include/ChessStateManager.hpp"

double ChessInterface::evaluateState(GameState* state) {
    return 1;
}

std::vector<GameState*>* ChessInterface::generatePossibleNextStates(GameState* state) {
    ChessStateManager* manager = new ChessStateManager(this->cast(state));
    std::vector<GameState*>* nextStates = manager->generatePossibleNextStates();
    delete manager;
    return nextStates;
}

GameState* ChessInterface::getEmptyState() {
    return ChessStateManager::getEmptyState();
}

ChessState* ChessInterface::cast(GameState* state) {
    return static_cast<ChessState*>(state);
} 