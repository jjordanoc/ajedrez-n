#ifndef PROYECTO_PAWN_H
#define PROYECTO_PAWN_H


#include "Piece.h"
namespace chess {
    class Pawn : public Piece {
    public:
        Pawn(const Color &color) : Piece(color) {
        }
        std::string repr() override {
            return "Pawn" + std::to_string(color);
        }
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, const std::array<std::array<std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> &boardData) override {
            std::vector<std::pair<PosType, PosType>> moves;
            short off;
            if (color == BLACK) {
                off = 1;
            } else {
                off = -1;
            }
            for (int i = -1; i <= 1; i += 2) {
                if (inBounds(fromRow + off, fromCol + i) && boardData.at(fromRow + off).at(fromCol + i) != nullptr) {
                    moves.emplace_back(fromRow + off, fromCol + i);
                }
            }
            if (inBounds(fromRow + off, fromCol) && boardData.at(fromRow + off).at(fromCol) == nullptr) {
                moves.emplace_back(fromRow + off, fromCol);
            }
            return moves;
        }
    };
}// namespace chess


#endif//PROYECTO_PAWN_H