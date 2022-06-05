#ifndef PROYECTO_ROOK_H
#define PROYECTO_ROOK_H


#include "Piece.h"
namespace chess {
//    bool hasMoved = false;
//    bool onJaque = false;
    class Rook : public Piece {
    public:
        Rook(const Color &color) : Piece(color) {

        }
        std::string repr() override {
            return "Rook" + std::to_string(color);
        }
        std::vector<std::pair<PosType, PosType>> possibleMoves(PosType fromRow, PosType fromCol, const std::array<std::array<std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> &boardData) override {
            std::vector<std::pair<PosType, PosType>> moves;
            std::vector<bool> flags(4, false);
            for (int i = 0; i <= BOARD_SIZE + 0; i++) {
                if (i == 0) {
                    continue;
                }
                const std::unordered_map<PosType, std::pair<short, short>> mappings = {
                        {0, {fromRow + i, fromCol}},
                        {1, {fromRow - i, fromCol}},
                        {2, {fromRow, fromCol - i}},
                        {3, {fromRow, fromCol - i}}
                };

                for (auto const &[key, pos] : mappings) {
                    if (!flags.at(key) && inBounds(pos.first, pos.second)) {
                        if (boardData.at(pos.first).at(pos.second) != nullptr) {
                            flags.at(key) = true;
                            if (boardData.at(pos.first).at(pos.second)->getColor() != color) {
                                if(boardData.at(pos.first).at(pos.second)->repr()  != "King0" && boardData.at(pos.first).at(pos.second)->repr()  != "King1"){
                                    moves.emplace_back(pos.first, pos.second);
                                }
                            }
                        } else {
                            moves.emplace_back(pos.first, pos.second);
                        }
                    }
                }
            }
            return moves;
        }

    };
}


#endif//PROYECTO_ROOK_H
