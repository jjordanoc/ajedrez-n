#include "Board.h"

chess::Board::Board() : pieceFactory(std::make_unique<PieceFactory>()) {
    for (auto &row: mainBoard) {
        for (auto &col: row) {
            col = nullptr;
        }
    }
}

void chess::Board::checkCastling(PosType oldRow, PosType oldCol, PosType newRow, PosType newCol) {
    if (!isMakingCastling) {
        auto king = mainBoard.at(oldRow).at(oldCol);
        if (std::dynamic_pointer_cast<King>(king) != nullptr) {
            if (newCol == 2) {
                std::cout << "Doing long castling" << std::endl;
                isMakingLongCastling = true;
                isMakingCastling = true;
            } else if (newCol == 6) {
                std::cout << "Doing short castling" << std::endl;
                isMakingShortCastling = true;
                isMakingCastling = true;
            }
        }
    }
}

bool chess::Board::movePiece(PosType oldRow, PosType oldCol, PosType newRow, PosType newCol) {
    if (!isMakingCastling) {
        if (mainBoard.at(newRow).at(newCol) == nullptr) {
            mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
            return true;
        } else if (mainBoard.at(newRow).at(newCol)->repr() != "King0" &&
                   mainBoard.at(newRow).at(newCol)->repr() != "King1") {
            mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
            // This statement it's not necessary because we can validate the possible moves and this isn't a possible move
            return true;
        }
    } else {
        // We move 2 pieces, the king and the rook
        auto king = mainBoard.at(oldRow).at(oldCol);

        if (isMakingShortCastling) {
            if (king->getColor() == BLACK) {
                mainBoard.at(0).at(3) = std::move(mainBoard.at(0).at(7));
                mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
                return true;
            } else {
                mainBoard.at(7).at(3) = std::move(mainBoard.at(7).at(7));
                mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
                return true;
            }
        } else if (isMakingLongCastling) {
            if (king->getColor() == BLACK) {
                mainBoard.at(0).at(3) = std::move(mainBoard.at(0).at(0));
                mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
                return true;
            } else {
                mainBoard.at(7).at(3) = std::move(mainBoard.at(7).at(0));
                mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
                return true;
            }
        }
        isMakingCastling = false;
        isMakingLongCastling = false;
        isMakingShortCastling = false;
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
                std::cout << "." << std::setw(10);
            }
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
}

void chess::Board::putKingChecked(const chess::Color &color) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = mainBoard.at(i).at(j);
            if (piece != nullptr) {
                if (color == BLACK) {
                    if (piece->repr() == "King0") {
                        std::cout << "Black king is checked" << "\n";
                        std::dynamic_pointer_cast<King>(piece)->setIsInCheck(true);
                    }
                } else if (color == WHITE) {
                    if (piece->repr() == "King1") {
                        std::cout << "White king is checked" << "\n";
                        std::dynamic_pointer_cast<King>(piece)->setIsInCheck(true);
                    }
                }
            }
        }
    }
}

bool chess::Board::isChecked(const chess::Color &color) {
    // check if any {{color}} piece is checking the other color's king
    Color other;
    if (color == WHITE) {
        other = BLACK;
    } else {
        other = WHITE;
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = mainBoard.at(i).at(j);
            if (piece != nullptr && piece->getColor() == other) {
                // update the piece
                piece->possibleMoves(i, j, mainBoard);
                // check if this piece is checking the king
                if (piece->getIsCheckingKing()) {
                    chess::Board::putKingChecked(color);
                    return true;
                }
            }
        }
    }
    return false;
}

bool chess::Board::isCheckMate() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = mainBoard.at(i).at(j);
            if (piece != nullptr && (piece->repr() == "King0" || piece->repr() == "King1")) {
                if (std::dynamic_pointer_cast<King>(piece)->isChecked &&
                    piece->possibleMoves(i, j, mainBoard).empty()) {
                    return true;
                }
            }
        }
    }
    return false;
}



