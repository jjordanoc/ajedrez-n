#ifndef PROYECTO_QUEEN_H
#define PROYECTO_QUEEN_H

#include "Piece.h"

namespace chess {
    class Queen : public Piece {
        std::string spriteD = "../../src/frontend/assets/textures/dark_queen.png";
        std::string spriteW = "../../src/frontend/assets/textures/white_queen.png";

    public:
        Queen(const Color &color);
        std::string repr() override;
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, Board &currentBoard) override;
        void verifyPossibleChecks(PosType fromRow, PosType fromCol, Board &currentBoard) override;
    };
}// namespace chess


#endif//PROYECTO_QUEEN_H
