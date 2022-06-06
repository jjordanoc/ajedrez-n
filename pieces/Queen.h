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
            std::vector<bool> flags(8, false);

            PosType numChecks = 0;
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (i == 0) {
                    continue;
                }
                const std::unordered_map<PosType, std::pair<short, short>> mappings = {
                        {0, {fromRow + i, fromCol + i}},
                        {1, {fromRow - i, fromCol + i}},
                        {2, {fromRow + i, fromCol - i}},
                        {3, {fromRow - i, fromCol - i}},
                        {4, {fromRow + i, fromCol}},
                        {5, {fromRow, fromCol + i}},
                        {6, {fromRow, fromCol - i}},
                        {7, {fromRow - i, fromCol}}};

                for (auto const &[key, pos]: mappings) {
                    if (!flags.at(key) && inBounds(pos.first, pos.second)) {
                        if (boardData.at(pos.first).at(pos.second) != nullptr) {
                            flags.at(key) = true;
                            if (boardData.at(pos.first).at(pos.second)->getColor() != color) {
                                if (boardData.at(pos.first).at(pos.second)->repr() != "King0" && boardData.at(pos.first).at(pos.second)->repr() != "King1") {
                                    moves.emplace_back(pos.first, pos.second);
                                } else {
                                    ++numChecks;
                                }
                            }
                        } else {
                            moves.emplace_back(pos.first, pos.second);
                        }
                    }
                }
            }

            if (numChecks != 0) {
                isCheckingKing = true;
            } else {
                isCheckingKing = false;
            }

            return moves;
        }
    };
}// namespace chess


#endif//PROYECTO_QUEEN_H
