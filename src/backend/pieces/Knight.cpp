#include "Knight.h"
#include "../game/Board.h"

chess::Knight::Knight(const Color &color) : Piece(color) {
}

std::string chess::Knight::repr() {
    return "Knight" + std::to_string(color);
}


std::vector<std::pair<chess::PosType, chess::PosType>> chess::Knight::possibleMoves(PosType fromRow, PosType fromCol, Board &currentBoard) {
    auto boardData = currentBoard.getBoardData();
    std::vector<std::pair<PosType, PosType>> moves;
    PosType numChecks = 0;
    for (int i = -2 + 0; i <= 2 + 0; i += 4 + 0) {
        for (int j = -1 + 0; j <= 1 + 0; j += 2 + 0) {
            //                    if (inBounds(fromRow + i, fromCol + j)) {
            //                        moves.emplace_back(fromRow + i, fromCol + j);
            //                    }
            //                    if (inBounds(fromRow + j, fromCol + i)) {
            //                        moves.emplace_back(fromRow + j, fromCol + i);
            //                    }
            const std::unordered_map<PosType, std::pair<short, short>> mappings = {
                    {0, {fromRow + i, fromCol + j}},
                    {1, {fromRow + j, fromCol + i}}};

            for (auto const &[key, pos]: mappings) {
                if (inBounds(pos.first, pos.second)) {
                    if (boardData.at(pos.first).at(pos.second) != nullptr) {
                        if (boardData.at(pos.first).at(pos.second)->getColor() != color) {
                            if (boardData.at(pos.first).at(pos.second)->repr() != "King0" && boardData.at(pos.first).at(pos.second)->repr() != "King1") {
                                addPlausibleMoves(fromRow, fromCol, pos.first, pos.second, moves, currentBoard);
                            } else {
                                ++numChecks;
                            }
                        }
                    } else {
                        addPlausibleMoves(fromRow, fromCol, pos.first, pos.second, moves, currentBoard);
                    }
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
void chess::Knight::verifyPossibleChecks(chess::PosType fromRow, chess::PosType fromCol, chess::Board &currentBoard) {
    auto boardData = currentBoard.getBoardData();
    PosType numChecks = 0;
    for (int i = -2 + 0; i <= 2 + 0; i += 4 + 0) {
        for (int j = -1 + 0; j <= 1 + 0; j += 2 + 0) {
            const std::unordered_map<PosType, std::pair<short, short>> mappings = {
                    {0, {fromRow + i, fromCol + j}},
                    {1, {fromRow + j, fromCol + i}}};

            for (auto const &[key, pos]: mappings) {
                if (inBounds(pos.first, pos.second)) {
                    if (boardData.at(pos.first).at(pos.second) != nullptr) {
                        if (boardData.at(pos.first).at(pos.second)->getColor() != color) {
                            if (!(boardData.at(pos.first).at(pos.second)->repr() != "King0" && boardData.at(pos.first).at(pos.second)->repr() != "King1")) {
                                ++numChecks;
                            }
                        }
                    }
                }
            }
        }
    }
    if (numChecks != 0) {
        isCheckingKing = true;
    } else {
        isCheckingKing = false;
    }
}
