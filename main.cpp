#include "chess/include/ChessStateManager.hpp"

int main() {
    ChessState* cs = ChessStateManager::generateStartingState();

    ChessStateManager::display(cs);

    
}