#ifndef PROYECTO_BISHOP_H
#define PROYECTO_BISHOP_H


#include "Piece.h"
namespace chess {
    class Bishop : public Piece {
        std::string spriteD = "../../src/frontend/assets/textures/dark_bishop.png";
        std::string spriteW = "../../src/frontend/assets/textures/white_bishop.png";

    public:
        Bishop(const Color &color);
        std::string repr() override;
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, Board &currentBoard) override;
        void verifyPossibleChecks(PosType fromRow, PosType fromCol, Board &currentBoard) override;
    };// namespace chess
}// namespace chess

#endif//PROYECTO_BISHOP_H
