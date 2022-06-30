#ifndef PROYECTO_KING_H
#define PROYECTO_KING_H

#include "Piece.h"

namespace chess {
    class King : public Piece {
        bool isChecked = false;
        std::string spriteD = "../../src/frontend/assets/textures/dark_king.png";
        std::string spriteW = "../../src/frontend/assets/textures/white_king.png";
    public:
        King(const Color &color);

        std::string repr() override;

        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, Board &boardData) override;
        void verifyPossibleChecks(PosType fromRow, PosType fromCol, Board &currentBoard) override;

        void setIsInCheck(bool i);
        bool getIsInCheck() const;
        bool checkIsCheck(PosType fromRow, PosType fromCol, PosType toRow, PosType toCol, Board &currentBoard);
        void drawPiece(sf::RenderWindow &window, PosType row, PosType col) override;
    };
}// namespace chess


#endif//PROYECTO_KING_H
