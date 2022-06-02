#ifndef PROYECTO_BISHOP_H
#define PROYECTO_BISHOP_H


#include "Piece.h"
namespace chess {
    class Bishop : public Piece {
    public:
        Bishop(const Color &color) : Piece(color) {
        }
        std::string repr() override {
            return "Bishop" + std::to_string(color);
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
            }
            return moves;
        }
    };
}// namespace chess


#endif//PROYECTO_BISHOP_H
