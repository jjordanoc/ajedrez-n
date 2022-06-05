#ifndef PROYECTO_PAWN_H
#define PROYECTO_PAWN_H


#include "Piece.h"
namespace chess {
    class Pawn : public Piece {
        bool hasMoved = false;
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
                // Enemy in pawn's diagonal
                if (inBounds(fromRow + off, fromCol + i)) {
                    if (boardData.at(fromRow + off).at(fromCol + i) != nullptr){
                        if (boardData.at(fromRow + off).at(fromCol + i)->getColor() != color){
                            if (boardData.at(fromRow + off).at(fromCol + i)->repr() != "King0" && boardData.at(fromRow + off).at(fromCol + i)->repr() != "King1") {
                                moves.emplace_back(fromRow + off, fromCol + i);
                            }
                        }
                    }
                }
            }
            // Empty in front of pawn
            if (inBounds(fromRow + off, fromCol) && boardData.at(fromRow + off).at(fromCol) == nullptr) {
                moves.emplace_back(fromRow + off, fromCol);
            }
            // if pawn hasn`t moved, it can move 2 steps
            if (!hasMoved){
                moves.emplace_back(fromRow + off + off, fromCol);
                hasMoved = true;
            }
            return moves;
        }
    };
}// namespace chess


#endif//PROYECTO_PAWN_H
