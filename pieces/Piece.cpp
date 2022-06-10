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
bool chess::Piece::getHasMoved() {
    return hasMoved;
}
void chess::Piece::setHasMoved(bool h) {
    hasMoved = h;
}
bool chess::Piece::getIsCheckingKing() {
    return isCheckingKing;
}
void chess::Piece::addPlausibleMoves(chess::PosType fromRow, chess::PosType fromCol, chess::PosType toRow, chess::PosType toCol, std::vector<std::pair<PosType, PosType>> &moves, Board &currentBoard) {
    // if our king is checked, the only plausible thing to do is to block the check or eat the piece checking
    if (currentBoard.isChecked(color)) {
        Board tmp(currentBoard);
        if (tmp.movePiece(fromRow, fromCol, toRow, toCol) && !tmp.isChecked(color)) {
            moves.emplace_back(toRow, toCol);
        }
    } else {
        moves.emplace_back(toRow, toCol);
    }
}
