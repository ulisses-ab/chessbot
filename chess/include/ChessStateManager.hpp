#include "ChessState.hpp"
#include <vector>

#ifndef CHESSESTATEMANAGER_H
#define CHESSESTATEMANAGER_H

class ChessStateManager {
public:
    ChessStateManager(ChessState* state);
    ChessStateManager(GameState* state);
    virtual ~ChessStateManager();

    static ChessState* generateStartingState();
    std::vector<GameState*>* generatePossibleNextStates();
    static ChessState* getEmptyState();
    void display();
    static void display(ChessState* state);
    static void display(GameState* state);
private:    
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
    bool hasPiece(int space);
    bool hasPiece(int piece, int space);

    int getAllyPieceInSpace(ChessState* state, int space);
    int getEnemyPieceInSpace(ChessState* state, int space);
    int getBlackPieceInSpace(ChessState* state, int space);
    int getWhitePieceInSpace(ChessState* state, int space);

    void generateWhitesBitboard();
    void generateBlacksBitboard();

    void generatePossibleMovesFromSpace(int space);
    void generatePawnMoves(int space);
    void generateRookMoves(int space);
    void generateKingMoves(int space);
    void generateQueenMoves(int space);
    void generateBishopMoves(int space);
    void generateKnightMoves(int space);
    void generateVerticalAndHorizontalMovesFor(int piece, int space);
    void generateDiagonalMovesFor(int piece, int space);

    void pushbackNewStateWithMovedPiece(int piece, int origin, int destination);
    ChessState* newStateWithMovedPiece(int piece, int origin, int destination);
    void movePieceInBitboard(long long unsigned int& bitboard, int origin, int destination);
    void removePieceInBitboard(long long unsigned int& bitboard, int space);
    void addPieceInBitboard(long long unsigned int& bitboard, int space);
    void clearSpaceInState(ChessState* state, int space);
    void removeWhitePieceInState(ChessState* state, int piece, int space);
    void removeBlackPieceInState(ChessState* state, int piece, int space);
    int row(int space);
    int column(int space);
    bool isSpaceValid(int space);

    void flipEnemyPieces();
    void flipEnemyPieces(ChessState* state);
    void flipWhitePieces(ChessState* state);
    void flipBlackPieces(ChessState* state);
    long long unsigned int flipLongLongUnsigned(long long unsigned int n);

    char getSpaceDisplayCharacter(int space);
    char getWhiteDisplayCharacter(int space);
    char getBlackDisplayCharacter(int space);

    long long unsigned int whitesBitboard, blacksBitboard;
    std::vector<GameState*>* possibleNextStates;
    ChessState* currentState;
};

#endif