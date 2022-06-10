#ifndef PROYECTO_QUEEN_H
#define PROYECTO_QUEEN_H

#include "Piece.h"
namespace chess {
    class Queen : public Piece {
    public:
        Queen(const Color &color);
        std::string repr() override;
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, Board &currentBoard) override;
    };
}// namespace chess


#endif//PROYECTO_QUEEN_H
