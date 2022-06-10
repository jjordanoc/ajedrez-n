#ifndef PROYECTO_ROOK_H
#define PROYECTO_ROOK_H


#include "Piece.h"
namespace chess {
    //    bool hasMoved = false;
    //    bool onJaque = false;
    class Rook : public Piece {
    public:
        Rook(const Color &color);
        std::string repr();
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, Board& currentBoard);
    };
}// namespace chess


#endif//PROYECTO_ROOK_H
