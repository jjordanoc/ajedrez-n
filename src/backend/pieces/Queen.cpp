#include "Queen.h"
#include "../game/Board.h"


chess::Queen::Queen(const chess::Color &color) : Piece(color) {
    value = 900;
    if (color == BLACK)
        pieceTexture.loadFromFile(spriteD);
    else if (color == WHITE)
        pieceTexture.loadFromFile(spriteW);

    pieceSprite.setTexture(pieceTexture);
}

std::string chess::Queen::repr() {
    return "Queen" + std::to_string(color);
}

std::vector<std::pair<chess::PosType, chess::PosType>> chess::Queen::possibleMoves(chess::PosType fromRow, chess::PosType fromCol, chess::Board &currentBoard) {
    auto boardData = currentBoard.getBoardData();

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
void chess::Queen::verifyPossibleChecks(chess::PosType fromRow, chess::PosType fromCol, chess::Board &currentBoard) {
    auto boardData = currentBoard.getBoardData();
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
