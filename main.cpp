#include "chess/include/ChessStateManager.hpp"
#include <iostream>

int main() {
    ChessState* cs = ChessStateManager::generateStartingState();

    ChessStateManager* csm = new ChessStateManager(cs);
    std::vector<GameState*>* moves = csm->generatePossibleNextStates();

    ChessStateManager::display(moves->at(7));
    ChessState* mv = static_cast<ChessState*>(moves->at(7));
    ChessStateManager* csm2 = new ChessStateManager(mv);
    std::vector<GameState*>* moves2 = csm2->generatePossibleNextStates();
    ChessState* mv2 = static_cast<ChessState*>(moves2->at(0));
    ChessStateManager::display(mv2);

    ChessStateManager* csm3 = new ChessStateManager(mv2);
    std::vector<GameState*>* moves3 = csm3->generatePossibleNextStates();
    ChessStateManager::display(moves3->at(0));
    ChessStateManager::display(moves3->at(1));
    ChessStateManager::display(moves3->at(2));
    ChessStateManager::display(moves3->at(3));
    ChessStateManager::display(moves3->at(4));
    ChessStateManager::display(moves3->at(5));
    ChessStateManager::display(moves3->at(6));
    ChessStateManager::display(moves3->at(7));
    ChessStateManager::display(moves3->at(8));
    ChessStateManager::display(moves3->at(9));
    ChessStateManager::display(moves3->at(10));
    ChessStateManager::display(moves3->at(11));
    ChessStateManager::display(moves3->at(12));
    ChessStateManager::display(moves3->at(13));
    ChessStateManager::display(moves3->at(14));
    ChessStateManager::display(moves3->at(15));
    ChessStateManager::display(moves3->at(16));
}