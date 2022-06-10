#ifndef PROYECTO_PIECE_H
#define PROYECTO_PIECE_H

#include <iostream>
#include <vector>
#include "../global/Global.h"
#include "../game/Board.h"




namespace chess {
    class Board;
    class Piece {
    protected:
        bool hasMoved = false;
        Color color;
        PosType value = 0;
        bool isCheckingKing = false;
        bool inBounds(int row, int col);
        virtual void addPlausibleMoves(PosType fromRow, PosType fromCol, PosType toRow, PosType toCol, std::vector<std::pair<PosType, PosType>> &moves, Board &currentBoard);
    public:
        Piece(const Color &color);
        Color getColor();
        bool getHasMoved();
        void setHasMoved(bool h);
        bool getIsCheckingKing();
        virtual std::string repr() = 0;
        virtual std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, Board &currentBoard) = 0;
    };
}


#endif
