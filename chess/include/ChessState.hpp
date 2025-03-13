#include "../../minimax/include/GameState.hpp"

#ifndef CHESSESTATE_H
#define CHESSESTATE_H

enum Pieces {
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    QUEEN,
    KING
};

struct ChessState : public GameState {
    bool whitesTurn;
    long long unsigned int whites[6];
    long long unsigned int blacks[6];
};

#endif