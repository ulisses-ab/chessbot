#include "../include/ChessStateManager.hpp"
#include <algorithm>
#include <iostream>

ChessStateManager::ChessStateManager(ChessState* state) {
    this->currentState = new ChessState();
    *this->currentState = *state;
    this->flipEnemyPieces();
    this->generateWhitesBitboard();
    this->generateBlacksBitboard();
}

ChessStateManager::~ChessStateManager() {
    delete this->currentState;
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

ChessState* ChessStateManager::getEmptyState() {
    return new ChessState();
}

ChessState* ChessStateManager::generateStartingState() {
    ChessState* chessStart = new ChessState();

    chessStart->whites[PAWN] =    0b0000000000000000000000000000000000000000000000001111111100000000;
    chessStart->whites[ROOK] =    0b0000000000000000000000000000000000000000000000000000000010000001;
    chessStart->whites[KNIGHT] =  0b0000000000000000000000000000000000000000000000000000000001000010;
    chessStart->whites[BISHOP] =  0b0000000000000000000000000000000000000000000000000000000000100100;
    chessStart->whites[QUEEN] =   0b0000000000000000000000000000000000000000000000000000000000010000;
    chessStart->whites[KING] =    0b0000000000000000000000000000000000000000000000000000000000001000;

    chessStart->blacks[PAWN] =    0b0000000000000000000000000000000000000000000000001111111100000000;
    chessStart->blacks[ROOK] =    0b0000000000000000000000000000000000000000000000000000000010000001;
    chessStart->blacks[KNIGHT] =  0b0000000000000000000000000000000000000000000000000000000001000010;
    chessStart->blacks[BISHOP] =  0b0000000000000000000000000000000000000000000000000000000000100100;
    chessStart->blacks[QUEEN] =   0b0000000000000000000000000000000000000000000000000000000000001000;
    chessStart->blacks[KING] =    0b0000000000000000000000000000000000000000000000000000000000010000;

    chessStart->whitesTurn = true;

    return chessStart;
}

std::vector<GameState*>* ChessStateManager::generatePossibleNextStates() {
    this->possibleNextStates = new std::vector<GameState*>();

    for(int space = 0; space < 64; space++) {
        this->generatePossibleMovesFromSpace(space);
    }

    return this->possibleNextStates;
}

void ChessStateManager::generatePossibleMovesFromSpace(int space) {
    if(!hasAlly(space)) return;

    if(hasAlly(PAWN, space)) {
        this->generatePawnMoves(space);
    }
    else if(hasAlly(KNIGHT, space)) {
        this->generateKnightMoves(space);
    }
    else if(hasAlly(BISHOP, space)) {
        this->generateBishopMoves(space);
    }
    else if(hasAlly(ROOK, space)) {
        this->generateRookMoves(space);
    }
    else if(hasAlly(QUEEN, space)) {
        this->generateQueenMoves(space);
    }
    else if(hasAlly(KING, space)) {
        this->generateKingMoves(space);
    }
}

void ChessStateManager::generatePawnMoves(int space) {
    if(space + 8 < 64 && this->isEmpty(space + 8)) {
        ChessState* newState = this->newStateWithMovedPiece(PAWN, space, space + 8);
        this->possibleNextStates->push_back(newState);
    }
}

void ChessStateManager::generateKnightMoves(int space) {

}

void ChessStateManager::generateKingMoves(int space) {

}

void ChessStateManager::generateRookMoves(int space) {

}

void ChessStateManager::generateQueenMoves(int space) {

}

void ChessStateManager::generateBishopMoves(int space) {

}

ChessState* ChessStateManager::newStateWithMovedPiece(int piece, int origin, int destination) {
    ChessState* newState = new ChessState();
    *newState = *(this->currentState);

    if(this->hasEnemy(destination)) {
        this->clearSpaceInState(newState, destination);
    }

    if(this->whitesTurn()) {
        newState->whites[piece] = movePieceInBitboard(newState->whites[piece], origin, destination);
    }
    else {
        newState->whites[piece] = movePieceInBitboard(newState->whites[piece], origin, destination);
    }

    return newState;
}

void ChessStateManager::clearSpaceInState(ChessState* state, int space) {
    int piece = this->getEnemyPieceInSpace(state, space);

    if(this->whitesTurn()) {
        this->removeBlackPieceInState(state, piece, space);
    }
    else {
        this->removeWhitePieceInState(state, piece, space);
    }
}

void ChessStateManager::removeWhitePieceInState(ChessState* state, int piece, int space) {
    state->whites[piece] = removePieceInBitboard(state->whites[piece], space);
}

void ChessStateManager::removeBlackPieceInState(ChessState* state, int piece, int space) {
    state->blacks[piece] = removePieceInBitboard(state->blacks[piece], space);
}

long long unsigned int ChessStateManager::movePieceInBitboard(long long unsigned int bitboard, int origin, int destination) {
    bitboard &= ~(1 << origin);
    bitboard |= (1 << destination);

    return bitboard;
}

long long unsigned int ChessStateManager::removePieceInBitboard(long long unsigned int bitboard, int space) {
    bitboard &= ~(1 << space);

    return bitboard;
}

long long unsigned int ChessStateManager::addPieceInBitboard(long long unsigned int bitboard, int space) {
    bitboard |= (1 << space);

    return bitboard;
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

bool ChessStateManager::hasBlack(int piece, int space) {
    return (1 << space) && this->currentState->blacks[piece];
}

bool ChessStateManager::isEmpty(int space) {
    return !this->hasWhite(space) && !this->hasBlack(space);
}

bool ChessStateManager::hasPiece(int space) {
    return !this->isEmpty(space);
}

bool ChessStateManager::hasPiece(int piece, int space) {
    return this->hasBlack(piece, space) || this->hasWhite(piece, space);
}

bool ChessStateManager::hasWhite(int space) {
    return (1 << space && this->whitesBitboard);
}

bool ChessStateManager::hasBlack(int space) {
    return (1 << space && this->blacksBitboard);
}

int ChessStateManager::getEnemyPieceInSpace(ChessState* state, int space) {
    if(this->whitesTurn()) {
        return this->getBlackPieceInSpace(state, space);
    }
    else {
        return this->getWhitePieceInSpace(state, space);
    }
}

int ChessStateManager::getAllyPieceInSpace(ChessState* state, int space) {
    if(this->blacksTurn()) {
        return this->getBlackPieceInSpace(state, space);
    }
    else {
        return this->getWhitePieceInSpace(state, space);
    }
}

int ChessStateManager::getWhitePieceInSpace(ChessState* state, int space) {
    if(this->hasWhite(PAWN, space)) {
        return PAWN;
    }
    else if(this->hasWhite(KNIGHT, space)) {
        return KNIGHT;
    }
    else if(this->hasWhite(BISHOP, space)) {
        return BISHOP;
    }
    else if(this->hasWhite(ROOK, space)) {
        return ROOK;
    }
    else if(this->hasWhite(QUEEN, space)) {
        return QUEEN;
    }
    else if(this->hasWhite(KING, space)) {
        return KING;
    }

    return -1;
}

int ChessStateManager::getBlackPieceInSpace(ChessState* state, int space) {
    if(this->hasBlack(PAWN, space)) {
        return PAWN;
    }
    else if(this->hasBlack(KNIGHT, space)) {
        return KNIGHT;
    }
    else if(this->hasBlack(BISHOP, space)) {
        return BISHOP;
    }
    else if(this->hasBlack(ROOK, space)) {
        return ROOK;
    }
    else if(this->hasBlack(QUEEN, space)) {
        return QUEEN;
    }
    else if(this->hasBlack(KING, space)) {
        return KING;
    }

    return -1;
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

void ChessStateManager::display(ChessState* state) {
    ChessStateManager* manager = new ChessStateManager(state);
    manager->display();
    delete manager;
}

void ChessStateManager::display() {
    for(int i = 7; i >= 0; i--) {
        std::cout << "+---+---+---+---+---+---+---+---+" << std::endl;
        for(int j = 7; j >= 0; j--) {
            int space = 8 * i + j;
            std::cout << "| " << this->getSpaceDisplayCharacter(space) << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "+---+---+---+---+---+---+---+---+" << std::endl;
}

char ChessStateManager::getSpaceDisplayCharacter(int space) {
    if(this->isEmpty(space)) return ' ';

    if(this->hasWhite(space)) {
        return this->getWhiteDisplayCharacter(space);
    }
    else {
        return this->getBlackDisplayCharacter(space);
    }
}

char ChessStateManager::getWhiteDisplayCharacter(int space) {
    if(hasWhite(PAWN, space)) {
        return 'P';
    }
    else if(hasWhite(KNIGHT, space)) {
        return 'N';
    }
    else if(hasWhite(BISHOP, space)) {
        return 'B';
    }
    else if(hasWhite(ROOK, space)) {
        return 'R';
    }
    else if(hasWhite(QUEEN, space)) {
        return 'Q';
    }
    else if(hasWhite(KING, space)) {
        return 'K';
    }

    return 'E';
}

char ChessStateManager::getBlackDisplayCharacter(int space) {
    if(hasBlack(PAWN, space)) {
        return 'p';
    }
    else if(hasBlack(KNIGHT, space)) {
        return 'n';
    }
    else if(hasBlack(BISHOP, space)) {
        return 'b';
    }
    else if(hasBlack(ROOK, space)) {
        return 'r';
    }
    else if(hasBlack(QUEEN, space)) {
        return 'q';
    }
    else if(hasAlly(KING, space)) {
        return 'k';
    }

    return 'e';
}

