#include "Pawn.h"
#include "../game/Board.h"

chess::Pawn::Pawn(const Color &color) : Piece(color) {
    value = 100;
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
                        addPlausibleMoves(fromRow, fromCol, fromRow + off, fromCol + i, moves, currentBoard);
                    } else {
                        ++numChecks;
                    }
                }
            } else {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    for (int k = 0; k < BOARD_SIZE; k++) {
                        auto piece = std::dynamic_pointer_cast<Pawn>(boardData.at(j).at(k));
                        // j, k are the position of the piece
                        if (piece != nullptr && piece->getColor() != color && piece->getIsEnPassant() &&  fromRow + off == j + off && fromCol + i == k) {
                            addPlausibleMoves(fromRow, fromCol, fromRow + off, fromCol + i, moves, currentBoard);
                        }
                    }
                }
            }
        }
    }
    // Empty in front of pawn
    if (inBounds(fromRow + off, fromCol) && boardData.at(fromRow + off).at(fromCol) == nullptr) {
        addPlausibleMoves(fromRow, fromCol, fromRow + off, fromCol, moves, currentBoard);
    }
    // if pawn hasn`t moved, it can move 2 steps
    if (inBounds(fromRow + off + off, fromCol) && moveCount == 0 && boardData.at(fromRow + off + off).at(fromCol) == nullptr) {
        addPlausibleMoves(fromRow, fromCol, fromRow + off + off, fromCol, moves, currentBoard);
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

void chess::Pawn::incrementMoveCount() {
    Piece::incrementMoveCount();
    if (moveCount > 1) {
        setIsEnPassant(false);
    }
}

void chess::Pawn::setIsEnPassant(bool value) {
    isEnPassant = value;
}
bool chess::Pawn::getIsEnPassant() {
    return isEnPassant;
}

void chess::Pawn::drawPiece(sf::RenderWindow &window, PosType row, PosType col) {

}
