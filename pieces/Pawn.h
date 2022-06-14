#ifndef PROYECTO_PAWN_H
#define PROYECTO_PAWN_H

#include "Piece.h"


namespace chess {
    class Pawn : public Piece {
        bool isEnPassant = false;
    public:
        Pawn(const Color &color);
        void incrementMoveCount() override;
        void setIsEnPassant(bool value);
        bool getIsEnPassant();
        std::string repr();
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, Board &currentBoard);
        void verifyPossibleChecks(PosType fromRow, PosType fromCol, Board &currentBoard) override;
    };
}// namespace chess


#endif//PROYECTO_PAWN_H