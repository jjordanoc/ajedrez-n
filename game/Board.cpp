#include "Board.h"

chess::Board::Board() : pieceFactory(std::make_unique<PieceFactory>()) {
    for (auto &row: mainBoard) {
        for (auto &col: row) {
            col = nullptr;
        }
    }
}




bool chess::Board::movePiece(PosType oldRow, PosType oldCol, PosType newRow, PosType newCol) {
    if (mainBoard.at(newRow).at(newCol) == nullptr) {
        mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
        return true;
    } else if (mainBoard.at(newRow).at(newCol)->repr()  != "King0" && mainBoard.at(newRow).at(newCol)->repr()  != "King1") {
        mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
        return true;
    }
    return false;
}

std::shared_ptr<chess::Piece> chess::Board::getPiece(PosType row, PosType col) {
    return mainBoard.at(row).at(col);
}

void chess::Board::putPiece(const std::string &pieceType, const Color &color, PosType row, PosType col) {
    mainBoard.at(row).at(col) = pieceFactory->create(pieceType, color);
}

void chess::Board::print() {
    std::cout << std::setw(10);
    for (const auto &row: mainBoard) {
        for (const auto &piece: row) {
            if (piece != nullptr) {
                std::cout << piece->repr() << std::setw(10);
            } else {
                std::cout << " " << std::setw(10);
            }
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
}
bool chess::Board::isChecked(const chess::Color &color) {
    // check if any {{color}} piece is checking the other color's king
    Color other;
    if (color == WHITE) {
        other = BLACK;
    }
    else {
        other = WHITE;
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = mainBoard.at(i).at(j);
            if (piece != nullptr && piece->getColor() == other) {
                // actualizar
                piece->possibleMoves(i, j, mainBoard);
                // obtener
                if (piece->getIsCheckingKing()) {
                    return true;
                }
            }
        }
    }
    return false;
}
