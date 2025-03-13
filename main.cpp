#include "chess/include/ChessStateManager.hpp"
#include <iostream>

int main() {
    ChessState* cs = ChessStateManager::generateStartingState();
    ChessStateManager* csm = new ChessStateManager(cs);
}