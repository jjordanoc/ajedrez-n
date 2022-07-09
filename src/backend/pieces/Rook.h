#ifndef PROYECTO_ROOK_H
#define PROYECTO_ROOK_H


#include "Piece.h"
namespace chess {
    class Rook : public Piece {
        std::string spriteD = "../../src/frontend/assets/textures/dark_rook.png";
        std::string spriteW = "../../src/frontend/assets/textures/white_rook.png";

    public:
        Rook(const Color &color);
        std::string repr();
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, Board &currentBoard);
        void verifyPossibleChecks(PosType fromRow, PosType fromCol, Board &currentBoard) override;
    };
}// namespace chess


#endif//PROYECTO_ROOK_H
