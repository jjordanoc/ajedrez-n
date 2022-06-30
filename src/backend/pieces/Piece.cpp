#include "Piece.h"
#include "../game/Board.h"

bool chess::Piece::inBounds(int row, int col) {
    return row >= 0 & row < 8 & col >= 0 & col < 8;
}
chess::Piece::Piece(const chess::Color &color) : color(color) {
}
chess::Color chess::Piece::getColor() {
    return color;
}

bool chess::Piece::getIsCheckingKing() {
    return isCheckingKing;
}

void chess::Piece::addPlausibleMoves(chess::PosType fromRow, chess::PosType fromCol, chess::PosType toRow, chess::PosType toCol, std::vector<std::pair<PosType, PosType>> &moves, Board &currentBoard) {
    // if our king is checked, the only plausible thing to do is to block the check or eat the piece checking
    Board tmp(currentBoard);
    tmp.movePiece(fromRow, fromCol, toRow, toCol);
    if (!tmp.isChecked(color)) {
        moves.emplace_back(toRow, toCol);
    }
}

chess::PosType chess::Piece::getMoveCount() {
    return moveCount;
}
void chess::Piece::incrementMoveCount() {
    ++moveCount;
}

int chess::Piece::getValue() const {
    return value;
}
