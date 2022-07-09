#include "Rook.h"
#include "../game/Board.h"
#include <cmath>

std::string chess::Rook::repr() {
    return "Rook" + std::to_string(color);
}

std::vector<std::pair<chess::PosType, chess::PosType>> chess::Rook::possibleMoves(PosType fromRow, PosType fromCol, Board &currentBoard) {
    auto boardData = currentBoard.getBoardData();
    std::vector<std::pair<PosType, PosType>> moves;
    std::vector<bool> flags(4, false);
    PosType numChecks = 0;
    // rooks can move at most ceil(|8 - log67(n)|) squares
    auto value = (std::log(currentBoard.getN()) / std::log(67));
    if (!inBounds(value, value)) {
        value = 0;
    }
    if (currentBoard.getN() == 0) {
        value = 0;
    }
    // find possible moves
    for (int i = 0; i <= std::ceil(std::abs(BOARD_SIZE - value)); i++) {
        if (i == 0) {
            continue;
        }
        const std::unordered_map<PosType, std::pair<short, short>> mappings = {
                {0, {fromRow + i, fromCol}},
                {1, {fromRow - i, fromCol}},
                {2, {fromRow, fromCol + i}},
                {3, {fromRow, fromCol - i}}};

        for (auto const &[key, pos]: mappings) {
            if (!flags.at(key) && inBounds(pos.first, pos.second)) {
                if (boardData.at(pos.first).at(pos.second) != nullptr) {
                    flags.at(key) = true;
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

    if (numChecks != 0) {
        isCheckingKing = true;
    } else {
        isCheckingKing = false;
    }
    return moves;
}
chess::Rook::Rook(const chess::Color &color) : Piece(color) {
    value = 500;
    if (color == BLACK)
        pieceTexture.loadFromFile(spriteD);
    else if (color == WHITE)
        pieceTexture.loadFromFile(spriteW);

    pieceSprite.setTexture(pieceTexture);
}

void chess::Rook::verifyPossibleChecks(chess::PosType fromRow, chess::PosType fromCol, chess::Board &currentBoard) {
    auto boardData = currentBoard.getBoardData();
    std::vector<bool> flags(4, false);
    PosType numChecks = 0;
    // rooks can move at most ceil(|8 - log67(n)|) squares
    auto value = (std::log(currentBoard.getN()) / std::log(67));
    if (!inBounds(value, value)) {
        value = 0;
    }
    if (currentBoard.getN() == 0) {
        value = 0;
    }
    // verify possible checks
    for (int i = 0; i <= std::ceil(std::abs(BOARD_SIZE - value)); i++) {
        if (i == 0) {
            continue;
        }
        const std::unordered_map<PosType, std::pair<short, short>> mappings = {
                {0, {fromRow + i, fromCol}},
                {1, {fromRow - i, fromCol}},
                {2, {fromRow, fromCol + i}},
                {3, {fromRow, fromCol - i}}};

        for (auto const &[key, pos]: mappings) {
            if (!flags.at(key) && inBounds(pos.first, pos.second)) {
                if (boardData.at(pos.first).at(pos.second) != nullptr) {
                    flags.at(key) = true;
                    if (boardData.at(pos.first).at(pos.second)->getColor() != color) {
                        if (!(boardData.at(pos.first).at(pos.second)->repr() != "King0" && boardData.at(pos.first).at(pos.second)->repr() != "King1")) {
                            ++numChecks;
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
