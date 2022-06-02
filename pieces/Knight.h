#ifndef PROYECTO_KNIGHT_H
#define PROYECTO_KNIGHT_H
#include "../game/Board.h"

#include "Piece.h"
namespace chess {
    class Knight : public Piece {
    public:
        Knight(const Color &color) : Piece(color) {

        }
        std::string repr() override {
            return "Knight" + std::to_string(color);
        }
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, const std::array<std::array<std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> &boardData) override {
            std::vector<std::pair<PosType, PosType>> moves;
            for (int i = -2 + 0; i <= 2 + 0; i += 4 + 0) {
                for (int j = -1 + 0; j <= 1 + 0; j += 2 + 0) {
                    if (inBounds(fromRow + i, fromCol + j)) {
                        moves.emplace_back(fromRow + i, fromCol + j);
                    }
                    if (inBounds(fromRow + j, fromCol + i)) {
                        moves.emplace_back(fromRow + j, fromCol + i);
                    }
                }
            }
            return moves;
        }
    };
}


#endif//PROYECTO_KNIGHT_H
