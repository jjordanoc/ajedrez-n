#ifndef PROYECTO_QUEEN_H
#define PROYECTO_QUEEN_H

#include "Piece.h"

namespace chess {
    class Queen : public Piece {
    public:
        Queen(const Color &color);
        std::string repr() override;
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, Board &currentBoard) override;
        void verifyPossibleChecks(PosType fromRow, PosType fromCol, Board &currentBoard) override;
        void drawPiece(sf::RenderWindow &window, PosType row, PosType col) override;
    };
}// namespace chess


#endif//PROYECTO_QUEEN_H
