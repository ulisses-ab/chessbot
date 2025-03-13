#include "../../minimax/include/GameState.hpp"

#ifndef CHESSESTATE_H
#define CHESSESTATE_H

enum Pieces {
    PAWNS,
    BISHOPS,
    KNIGHTS,
    ROOKS,
    QUEENS,
    KINGS
};

struct ChessState : public GameState {
    bool whitesTurn;
    long long unsigned int whites[5];
    long long unsigned int blacks[5];
};

#endif