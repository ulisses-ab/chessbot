#include "../include/ChessStateManager.hpp"
#include <algorithm>
#include <iostream>

ChessStateManager::ChessStateManager(GameState* state) {
    ChessStateManager(static_cast<ChessState*>(state));
}


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
    this->flipEnemyPieces(this->currentState);
}

void ChessStateManager::flipEnemyPieces(ChessState* state) {
    if(state->whitesTurn) {
        this->flipBlackPieces(state);
    }
    else {
        this->flipWhitePieces(state);
    }
}

void ChessStateManager::flipBlackPieces(ChessState* state) {
    for(auto& pieces : state->blacks) {
        pieces = this->flipLongLongUnsigned(pieces);
    }
}

void ChessStateManager::flipWhitePieces(ChessState* state) {
    for(auto& pieces : state->whites) {
        pieces = this->flipLongLongUnsigned(pieces);
    }
}


long long unsigned int ChessStateManager::flipLongLongUnsigned(long long unsigned int n) {
    long long unsigned int temp = 0;

    for(int i = 0; i < 64; i++) {
        if(n & (1llu << i)) {
            temp |= (1llu << (63 - i));
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
    if(this->isEmpty(space + 8)) {
        this->pushbackNewStateWithMovedPiece(PAWN, space, space + 8);

        if(this->row(space + 8) == 1 && this->isEmpty(space + 16)) {
            this->pushbackNewStateWithMovedPiece(PAWN, space, space + 16);
        }
    }

    if(this->column(space + 7) != 7 && this->hasEnemy(space + 7)) {
        this->pushbackNewStateWithMovedPiece(PAWN, space, space + 7);
    }

    if(this->column(space + 9) != 0 && this->hasEnemy(space + 9)) {
        this->pushbackNewStateWithMovedPiece(PAWN, space, space + 9);
    }
}

void ChessStateManager::generateKnightMoves(int space) {
    if(this->column(space + 15) != 7 && !this->hasAlly(space + 15)) {
        this->pushbackNewStateWithMovedPiece(KNIGHT, space, space + 15);
    }

    if(this->column(space + 17) != 0 && !this->hasAlly(space + 17)) {
        this->pushbackNewStateWithMovedPiece(KNIGHT, space, space + 17);
    }

    if(this->column(space + 6) < 6 && !this->hasAlly(space + 6)) {
        this->pushbackNewStateWithMovedPiece(KNIGHT, space, space + 6);
    }

    if(this->column(space + 10) > 1 && !this->hasAlly(space + 10)) {
        this->pushbackNewStateWithMovedPiece(KNIGHT, space, space + 10);
    }

    if(this->column(space - 17) != 7 && !this->hasAlly(space - 17)) {
        this->pushbackNewStateWithMovedPiece(KNIGHT, space, space - 17);
    }

    if(this->column(space - 15) != 0 && !this->hasAlly(space - 15)) {
        this->pushbackNewStateWithMovedPiece(KNIGHT, space, space - 15);
    }

    if(this->column(space - 10) < 6 && !this->hasAlly(space - 10)) {
        this->pushbackNewStateWithMovedPiece(KNIGHT, space, space - 10);
    }

    if(this->column(space - 6) > 1 && !this->hasAlly(space - 6)) {
        this->pushbackNewStateWithMovedPiece(KNIGHT, space, space - 6);
    }
}

void ChessStateManager::generateKingMoves(int space) {
    if(this->column(space + 7) != 7 && !this->hasAlly(space + 7)) {
        this->pushbackNewStateWithMovedPiece(KING, space, space + 7);
    }
    if(this->column(space - 1) != 7 && !this->hasAlly(space - 1)) {
        this->pushbackNewStateWithMovedPiece(KING, space, space - 1);
    }
    if(this->column(space - 9) != 7 && !this->hasAlly(space - 9)) {
        this->pushbackNewStateWithMovedPiece(KING, space, space - 9);
    }
    if(this->column(space + 9) != 0 && !this->hasAlly(space + 9)) {
        this->pushbackNewStateWithMovedPiece(KING, space, space + 9);
    }
    if(this->column(space - 7) != 0 && !this->hasAlly(space - 7)) {
        this->pushbackNewStateWithMovedPiece(KING, space, space - 7);
    }
    if(this->column(space + 1) != 0 && !this->hasAlly(space + 1)) {
        this->pushbackNewStateWithMovedPiece(KING, space, space + 1);
    }
    if(!this->hasAlly(space + 8)) {
        this->pushbackNewStateWithMovedPiece(KING, space, space + 8);
    }
    if(!this->hasAlly(space - 8)) {
        this->pushbackNewStateWithMovedPiece(KING, space, space - 8);
    }

}

void ChessStateManager::generateRookMoves(int space) {
    this->generateVerticalAndHorizontalMovesFor(ROOK, space);
}

void ChessStateManager::generateQueenMoves(int space) {
    this->generateVerticalAndHorizontalMovesFor(QUEEN, space);
    this->generateDiagonalMovesFor(QUEEN, space);
}

void ChessStateManager::generateBishopMoves(int space) {
    this->generateDiagonalMovesFor(BISHOP, space);
}

void ChessStateManager::generateVerticalAndHorizontalMovesFor(int piece, int space) {
    for(int nextSpace = space + 8; nextSpace < 64; nextSpace += 8) {
        if(this->hasAlly(nextSpace)) {
            break;
        }

        this->pushbackNewStateWithMovedPiece(piece, space, nextSpace);

        if(this->hasEnemy(nextSpace)) {
            break;
        }
    }

    for(int nextSpace = space - 8; nextSpace >= 0; nextSpace -= 8) {
        if(this->hasAlly(nextSpace)) {
            break;
        }

        this->pushbackNewStateWithMovedPiece(piece, space, nextSpace);

        if(this->hasEnemy(nextSpace)) {
            break;
        }
    }

    for(int nextSpace = space + 1; this->column(nextSpace) != 0; nextSpace += 1) {
        if(this->hasAlly(nextSpace)) {
            break;
        }

        this->pushbackNewStateWithMovedPiece(piece, space, nextSpace);

        if(this->hasEnemy(nextSpace)) {
            break;
        }
    }

    for(int nextSpace = space - 1; this->column(nextSpace) != 7; nextSpace -= 1) {
        if(this->hasAlly(nextSpace)) {
            break;
        }

        this->pushbackNewStateWithMovedPiece(piece, space, nextSpace);

        if(this->hasEnemy(nextSpace)) {
            break;
        }
    }

}

void ChessStateManager::generateDiagonalMovesFor(int piece, int space) {
    for(int nextSpace = space + 7; nextSpace < 64 && this->column(nextSpace) != 7; nextSpace += 7) {
        if(this->hasAlly(nextSpace)) {
            break;
        }

        this->pushbackNewStateWithMovedPiece(piece, space, nextSpace);

        if(this->hasEnemy(nextSpace)) {
            break;
        }
    } 

    for(int nextSpace = space + 9; nextSpace < 64 && this->column(nextSpace) != 0; nextSpace += 9) {
        if(this->hasAlly(nextSpace)) {
            break;
        }

        this->pushbackNewStateWithMovedPiece(piece, space, nextSpace);

        if(this->hasEnemy(nextSpace)) {
            break;
        }
    } 

    for(int nextSpace = space - 7; nextSpace >= 0 && this->column(nextSpace) != 0; nextSpace -= 7) {
        if(this->hasAlly(nextSpace)) {
            break;
        }

        this->pushbackNewStateWithMovedPiece(piece, space, nextSpace);

        if(this->hasEnemy(nextSpace)) {
            break;
        }
    } 

    for(int nextSpace = space - 9; nextSpace >= 0 && this->column(nextSpace) != 7; nextSpace -= 9) {
        if(this->hasAlly(nextSpace)) {
            break;
        }

        this->pushbackNewStateWithMovedPiece(piece, space, nextSpace);

        if(this->hasEnemy(nextSpace)) {
            break;
        }
    } 
}

bool ChessStateManager::isSpaceValid(int space) {
    return space < 64 && space >= 0;
}

int ChessStateManager::row(int space) {
    return space / 8;
}

int ChessStateManager::column(int space) {
    return space % 8;
}

void ChessStateManager::pushbackNewStateWithMovedPiece(int piece, int origin, int destination) {
    if(!this->isSpaceValid(destination)) return;

    ChessState* newState = this->newStateWithMovedPiece(piece, origin, destination);
    this->flipEnemyPieces(newState);
    newState->whitesTurn = !newState->whitesTurn;
    this->possibleNextStates->push_back(newState);
}

ChessState* ChessStateManager::newStateWithMovedPiece(int piece, int origin, int destination) {
    ChessState* newState = new ChessState();
    *newState = *(this->currentState);

    if(this->hasEnemy(destination)) {
        this->clearSpaceInState(newState, destination);
    }

    if(this->whitesTurn()) {
        movePieceInBitboard(newState->whites[piece], origin, destination);
    }
    else {
        movePieceInBitboard(newState->blacks[piece], origin, destination);
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
    removePieceInBitboard(state->whites[piece], space);
}

void ChessStateManager::removeBlackPieceInState(ChessState* state, int piece, int space) {
    removePieceInBitboard(state->blacks[piece], space);
}

void ChessStateManager::movePieceInBitboard(long long unsigned int& bitboard, int origin, int destination) {
    bitboard &= ~(1llu << origin);
    bitboard |= (1llu << destination);
}

void ChessStateManager::removePieceInBitboard(long long unsigned int& bitboard, int space) {
    bitboard &= ~(1llu << space);
}

void ChessStateManager::addPieceInBitboard(long long unsigned int& bitboard, int space) {
    bitboard |= (1llu << space);
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
    return (1llu << space) & this->currentState->whites[piece];
}

bool ChessStateManager::hasBlack(int piece, int space) {
    return (1llu << space) & this->currentState->blacks[piece];
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
    return (1llu << space & this->whitesBitboard);
}

bool ChessStateManager::hasBlack(int space) {
    return (1llu << space & this->blacksBitboard);
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


void ChessStateManager::display(GameState* state) {
    ChessStateManager::display(static_cast<ChessState*>(state));
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
    else if(hasBlack(KING, space)) {
        return 'k';
    }

    return 'e';
}

