#ifndef PROYECTO_PIECE_H
#define PROYECTO_PIECE_H

#include <iostream>
#include <vector>
#include "../global/Global.h"
#include "../game/Board.h"



namespace chess {
    class Piece {
    protected:
        Color color;
        PosType value = 0;
        bool isCheckingKing = false;
        bool inBounds(int row, int col) {
            return row >= 0 & row < 8 & col >= 0 & col < 8;
        }
    public:
        Piece(const Color &color) : color(color) {

        }
        Color getColor() {
            return color;
        }
        bool getIsCheckingKing() {
            return isCheckingKing;
        }
        virtual std::string repr() = 0;
        virtual std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, const std::array<std::array<std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> &boardData) = 0;

    };
}


#endif
