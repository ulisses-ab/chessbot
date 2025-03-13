#include "../../minimax/include/StateManager.hpp"
#include "ChessState.hpp"

#ifndef CHESSESTATEMANAGER_H
#define CHESSESTATEMANAGER_H

class ChessStateManager : public StateManager {
public:
    GameState* generateStartingState();
    std::vector<GameState*>* generatePossibleNextStates(GameState* state);
    bool isTerminalState(GameState* state);
    GameState* getEmptyState();
private:
    void initializeNewState(GameState* state);
    
    bool whitesTurn();
    bool blacksTurn();

    bool hasBlack(int space);
    bool hasWhite(int space);
    bool hasBlack(int piece, int space);
    bool hasWhite(int piece, int space);

    bool hasAlly(int space);
    bool hasEnemy(int space);
    bool hasAlly(int piece, int space);
    bool hasEnemy(int piece, int space);

    bool isEmpty(int space);

    void generateWhitesBitboard();
    void generateBlacksBitboard();

    void generatePossibleMovesFromSpace(int space);
    void generatePawnMoves(int space);
    void generateRookMoves(int space);
    void generateKingMoves(int space);
    void generateQueenMoves(int space);
    void generateBishopMoves(int space);
    void generateKnightMoves(int space);

    void flipEnemyPieces();
    void flipWhitePieces();
    void flipBlackPieces();

    long long unsigned int flipLongLongUnsigned(long long unsigned int n);

    long long unsigned int whitesBitboard, blacksBitboard;
    std::vector<GameState*>* possibleNextStates;
    ChessState* currentState;
};

#endif