#ifndef PROYECTO_KNIGHT_H
#define PROYECTO_KNIGHT_H

#include "Piece.h"
namespace chess {
    class Knight : public Piece {
    public:
        Knight(const Color &color);
        std::string repr();
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, Board &currentBoard);
        void verifyPossibleChecks(PosType fromRow, PosType fromCol, Board &currentBoard) override;
    };
}// namespace chess


#endif//PROYECTO_KNIGHT_H
