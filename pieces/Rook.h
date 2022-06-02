#ifndef PROYECTO_ROOK_H
#define PROYECTO_ROOK_H


#include "Piece.h"
namespace chess {
    class Rook : public Piece {
    public:
        Rook(const Color &color) : Piece(color) {

        }
        std::string repr() override {
            return "Rook" + std::to_string(color);
        }
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, const std::array<std::array<std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> &boardData) override {
            std::vector<std::pair<PosType, PosType>> moves;
            for (int i = -8 + 0; i <= 8 + 0; i++) {
                if (i == 0) {
                    continue;
                }
                if (inBounds(fromRow + i, fromCol)) {
                    moves.emplace_back(fromRow + i, fromCol);
                }
                if (inBounds(fromRow, fromCol + i)) {
                    moves.emplace_back(fromRow, fromCol + i);
                }
            }
            return moves;
        }

    };
}


#endif//PROYECTO_ROOK_H
