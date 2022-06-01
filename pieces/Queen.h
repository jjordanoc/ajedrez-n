#ifndef PROYECTO_QUEEN_H
#define PROYECTO_QUEEN_H

#include "Piece.h"
namespace chess {
    class Queen : public Piece {
    public:
        Queen(const Color &color) : Piece(color) {
        }
        std::string repr() override {
            return "Queen" + std::to_string(color);
        }
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, const std::array<std::array<std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> &boardData) override {
            std::vector<std::pair<PosType, PosType>> moves;

            for (int i = 0; i < BOARD_SIZE; i++) {
                if (i == 0) {
                    continue;
                }
                if (inBounds(fromRow + i, fromCol + i)) {
                    moves.emplace_back(fromRow + i, fromCol + i);
                }
                if (inBounds(fromRow + i, fromCol - i)) {
                    moves.emplace_back(fromRow + i, fromCol - i);
                }
                if (inBounds(fromRow - i, fromCol + i)) {
                    moves.emplace_back(fromRow - i, fromCol + i);
                }
                if (inBounds(fromRow - i, fromCol - i)) {
                    moves.emplace_back(fromRow - i, fromCol - i);
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
}// namespace chess


#endif//PROYECTO_QUEEN_H
