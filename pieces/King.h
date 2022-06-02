#ifndef PROYECTO_KING_H
#define PROYECTO_KING_H

#include "Piece.h"
namespace chess {
    class King : public Piece {
    public:
        King(const Color &color) : Piece(color) {
        }
        std::string repr() override {
            return "King" + std::to_string(color);
        }
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, const std::array<std::array<std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> &boardData) override {
            std::vector<std::pair<PosType, PosType>> moves;
            for (int i = -1; i <= 1; i += 1) {
                for (int j = -1; j <= 1; j += 1) {
                        if (i == 0 && j == 0) {
                            continue;
                        }
                    if (inBounds(fromRow + i, fromCol + j)) {
                        moves.emplace_back(fromRow + i, fromCol + j);
                    }
                }
            }
            return moves;
        }
    };
}


#endif//PROYECTO_KING_H
