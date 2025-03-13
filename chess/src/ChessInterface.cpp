#include "../include/ChessInterface.hpp"

ChessInterface::ChessInterface() : GameInterface(new ChessEvaluator(), new ChessStateManager()) {

}
