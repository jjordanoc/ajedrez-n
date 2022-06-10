#ifndef PROYECTO_KING_H
#define PROYECTO_KING_H

#include "Piece.h"

namespace chess {
    class King : public Piece {
        bool isChecked = false;

    public:
        King(const Color &color);

        std::string repr() override;

        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, Board &boardData) override;

        void setIsInCheck(bool i);
        bool getIsInCheck() const;
    };
}// namespace chess


#endif//PROYECTO_KING_H
