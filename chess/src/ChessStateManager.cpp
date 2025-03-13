#include "ChessStateManager.hpp"
#include <algorithm>
#include "ChessState.hpp"

GameState* ChessStateManager::getEmptyState() {
    return new ChessState();
}

GameState* ChessStateManager::generateStartingState() {
    ChessState* chessStart = new ChessState();

    chessStart->whites[PAWNS] =  0b0000000000000000000000000000000000000000000000001111111100000000;
    chessStart->whites[ROOKS] =    0b0000000000000000000000000000000000000000000000000000000010000001;
    chessStart->whites[KNIGHTS] =  0b0000000000000000000000000000000000000000000000000000000001000010;
    chessStart->whites[BISHOPS] =  0b0000000000000000000000000000000000000000000000000000000000100100;
    chessStart->whites[QUEENS] =   0b0000000000000000000000000000000000000000000000000000000000010000;
    chessStart->whites[KINGS] =    0b0000000000000000000000000000000000000000000000000000000000001000;

    chessStart->blacks[PAWNS] =    0b0000000000000000000000000000000000000000000000001111111100000000;
    chessStart->blacks[ROOKS] =    0b0000000000000000000000000000000000000000000000000000000010000001;
    chessStart->blacks[KNIGHTS] =  0b0000000000000000000000000000000000000000000000000000000001000010;
    chessStart->blacks[BISHOPS] =  0b0000000000000000000000000000000000000000000000000000000000100100;
    chessStart->blacks[QUEENS] =   0b0000000000000000000000000000000000000000000000000000000000001000;
    chessStart->blacks[KINGS] =    0b0000000000000000000000000000000000000000000000000000000000010000;

    chessStart->whitesTurn = true;

    return chessStart;
}

std::vector<GameState*>* ChessStateManager::generatePossibleNextStates(GameState* gameState) {
    this->initializeNewState(gameState);

    for(int space = 0; space < 64; space++) {
        this->generatePossibleMovesFromSpace(space);
    }
}

void ChessStateManager::initializeNewState(GameState* gameState) {
    ChessState* state = static_cast<ChessState*>(gameState);
    this->currentState = new ChessState();
    *this->currentState = *state;
    this->possibleNextStates = new std::vector<GameState*>();
    this->flipEnemyPieces();
    this->generateWhitesBitboard();
    this->generateBlacksBitboard();
}

void ChessStateManager::flipEnemyPieces() {
    if(this->whitesTurn()) {
        this->flipWhitePieces();
    }
    else {
        this->flipBlackPieces();
    }
}

void ChessStateManager::flipBlackPieces() {
    for(auto& pieces : this->currentState->blacks) {
        pieces = this->flipLongLongUnsigned(pieces);
    }
}

void ChessStateManager::flipWhitePieces() {
    for(auto& pieces : this->currentState->whites) {
        pieces = this->flipLongLongUnsigned(pieces);
    }
}

long long unsigned int ChessStateManager::flipLongLongUnsigned(long long unsigned int n) {
    long long unsigned int temp = 0;

    for(int i = 0; i < 64; i++) {
        if(n && (1 << i)) {
            temp |= (1 << (63 - i));
        } 
    }

    return temp;
}

void ChessStateManager::generatePossibleMovesFromSpace(int space) {
    if(!hasAlly(space)) return;

    if(hasAlly(PAWNS, space)) {
        this->generatePawnMoves(space);
    }
    else if(hasAlly(KNIGHTS, space)) {
        this->generateKnightMoves(space);
    }
    else if(hasAlly(BISHOPS, space)) {
        this->generateBishopMoves(space);
    }
    else if(hasAlly(ROOKS, space)) {
        this->generateRookMoves(space);
    }
    else if(hasAlly(QUEENS, space)) {
        this->generateQueenMoves(space);
    }
    else if(hasAlly(KINGS, space)) {
        this->generateKingMoves(space);
    }
}

void ChessStateManager::generatePawnMoves(int space) {
    
}

bool ChessStateManager::hasEnemy(int piece, int space) {
    return this->whitesTurn() ? this->hasBlack(piece, space) : this->hasWhite(piece, space); 
}

bool ChessStateManager::hasAlly(int piece, int space) {
    return this->blacksTurn() ? this->hasBlack(piece, space) : this->hasWhite(piece, space); 
}

bool ChessStateManager::hasEnemy(int space) {
    return this->whitesTurn() ? this->hasBlack(space) : this->hasWhite(space); 
}

bool ChessStateManager::hasAlly(int space) {
    return this->blacksTurn() ? this->hasBlack(space) : this->hasWhite(space); 
}

bool ChessStateManager::whitesTurn() {
    return this->currentState->whitesTurn;
}

bool ChessStateManager::blacksTurn() {
    return !this->currentState->whitesTurn;
}

bool ChessStateManager::hasWhite(int piece, int space) {
    return (1 << space) && this->currentState->whites[piece];
}

bool ChessStateManager::hasWhite(int piece, int space) {
    return (1 << space) && this->currentState->blacks[piece];
}

bool ChessStateManager::isEmpty(int space) {
    return !this->hasWhite(space) && !this->hasBlack(space);
}

bool ChessStateManager::hasWhite(int space) {
    return (1 << space && this->whitesBitboard);
}

bool ChessStateManager::hasBlack(int space) {
    return (1 << space && this->blacksBitboard);
}

void ChessStateManager::generateWhitesBitboard() {
    long long unsigned int bitboard = 0;

    for(auto pieces : this->currentState->whites) {
        bitboard |= pieces;
    }

    this->whitesBitboard = bitboard;
}

void ChessStateManager::generateBlacksBitboard() {
    long long unsigned int bitboard = 0;

    for(auto pieces : this->currentState->blacks) {
        bitboard |= pieces;
    }

    this->blacksBitboard = bitboard;
}

bool ChessStateManager::isTerminalState(GameState* state) {

}