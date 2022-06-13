#include "Pawn.h"
#include "../game/Board.h"

chess::Pawn::Pawn(const Color &color) : Piece(color) {
}

std::string chess::Pawn::repr() {
    return "Pawn" + std::to_string(color);
}

std::vector<std::pair<chess::PosType, chess::PosType>> chess::Pawn::possibleMoves(chess::PosType fromRow, chess::PosType fromCol, Board &currentBoard) {
    auto boardData = currentBoard.getBoardData();
    std::vector<std::pair<PosType, PosType>> moves;
    short off;
    if (color == BLACK) {
        off = 1;
    } else {
        off = -1;
    }
    PosType numChecks = 0;
    for (int i = -1; i <= 1; i += 2) {
        // Enemy in pawn's diagonal
        if (inBounds(fromRow + off, fromCol + i)) {
            if (boardData.at(fromRow + off).at(fromCol + i) != nullptr) {
                if (boardData.at(fromRow + off).at(fromCol + i)->getColor() != color) {
                    if (boardData.at(fromRow + off).at(fromCol + i)->repr() != "King0" && boardData.at(fromRow + off).at(fromCol + i)->repr() != "King1") {
                        moves.emplace_back(fromRow + off, fromCol + i);
                    } else {
                        ++numChecks;
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
    if (!hasMoved && boardData.at(fromRow + off + off).at(fromCol) == nullptr) {
        moves.emplace_back(fromRow + off + off, fromCol);
    }
    if (numChecks != 0) {
        isCheckingKing = true;
    } else {
        isCheckingKing = false;
    }
    return moves;
}
void chess::Pawn::verifyPossibleChecks(chess::PosType fromRow, chess::PosType fromCol, chess::Board &currentBoard) {
    auto boardData = currentBoard.getBoardData();
    short off;
    if (color == BLACK) {
        off = 1;
    } else {
        off = -1;
    }
    PosType numChecks = 0;
    for (int i = -1; i <= 1; i += 2) {
        // Enemy in pawn's diagonal
        if (inBounds(fromRow + off, fromCol + i)) {
            if (boardData.at(fromRow + off).at(fromCol + i) != nullptr) {
                if (boardData.at(fromRow + off).at(fromCol + i)->getColor() != color) {
                    if (!(boardData.at(fromRow + off).at(fromCol + i)->repr() != "King0" && boardData.at(fromRow + off).at(fromCol + i)->repr() != "King1")) {
                        ++numChecks;
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
