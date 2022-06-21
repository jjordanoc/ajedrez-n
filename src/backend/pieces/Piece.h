#ifndef PROYECTO_PIECE_H
#define PROYECTO_PIECE_H

#include <iostream>
#include <vector>
#include "../global/Global.h"




namespace chess {
    class Board;
    class Piece {
    protected:
        PosType moveCount = 0;
        Color color;
        int value = 0;
        bool isCheckingKing = false;
        bool inBounds(int row, int col);
        void addPlausibleMoves(PosType fromRow, PosType fromCol, PosType toRow, PosType toCol, std::vector<std::pair<PosType, PosType>> &moves, Board &currentBoard);
    public:
        Piece(const Color &color);
        Color getColor();
        PosType getMoveCount();
        virtual void incrementMoveCount();
        bool getIsCheckingKing();
        virtual std::string repr() = 0;
        virtual void verifyPossibleChecks(PosType fromRow, PosType fromCol, Board &currentBoard) = 0;
        virtual std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, Board &currentBoard) = 0;
        int getValue() const;
    };
}


#endif
