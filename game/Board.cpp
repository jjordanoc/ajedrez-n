#include "Board.h"

chess::Board::Board() : pieceFactory(std::make_shared<PieceFactory>()) {
    for (auto &row: mainBoard) {
        for (auto &col: row) {
            col = nullptr;
        }
    }
}

chess::Board::Board(const chess::Board &another) {
    mainBoard = another.mainBoard;
    isMakingCastling = another.isMakingCastling;
    isMakingLongCastling = another.isMakingLongCastling;
    isMakingShortCastling = another.isMakingShortCastling;
    pieceFactory = another.pieceFactory;
}

void chess::Board::checkPawnPromotion(PosType newRow, PosType newCol) {
    auto piece = mainBoard.at(newRow).at(newCol);
    // If the piece is a pawn
    if (std::dynamic_pointer_cast<Pawn>(piece) != nullptr) {
        Color PawnColor = piece->getColor();
        // If black pawn is in the row 7 or white pawn is in the row 0, that pawn is promoted
        if (PawnColor == BLACK && newRow == 7) {
            std::string name;
            std::cout << "Black Pawn Promoted" << std::endl;
            std::cout << "Write the name of the piece you wanna change it to (except the King) e.i Queen: ";
            std::cin >> name;
            mainBoard.at(newRow).at(newCol) = nullptr;
            putPiece(name, PawnColor, newRow, newCol);
        } else if (PawnColor == WHITE && newRow == 0) {
            std::string name;
            std::cout << "White Pawn Promoted" << std::endl;
            std::cout << "Write the name of the piece you wanna change it to (except the King) e.i Queen: ";
            std::cin >> name;
            mainBoard.at(newRow).at(newCol) = nullptr;
            putPiece(name, PawnColor, newRow, newCol);
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
                mainBoard.at(0).at(5) = std::move(mainBoard.at(0).at(7));
                mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
                return true;
            } else {
                mainBoard.at(7).at(5) = std::move(mainBoard.at(7).at(7));
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

void chess::Board::print() const {
    std::cout << std::setw(20);
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << i << std::setw(10);
    }
    std::cout << std::endl;

    int count = 0;
    for (const auto &row: mainBoard) {
        if (row == mainBoard.at(count)) {
            std::cout << count << std::setw(10);
            count++;
        }
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
                        std::dynamic_pointer_cast<King>(piece)->setIsInCheck(true);
                    }
                } else if (color == WHITE) {
                    if (piece->repr() == "King1") {
                        std::dynamic_pointer_cast<King>(piece)->setIsInCheck(true);
                    }
                }
            }
        }
    }
}

bool chess::Board::isChecked(const chess::Color &color) {
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
                piece->possibleMoves(i, j, *this);
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

bool chess::Board::isCheckMate(const Color &color) {
    Color other;
    if (color == WHITE) {
        other = BLACK;
    } else {
        other = WHITE;
    }
    if (!isChecked(other)) {
        return false;
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = mainBoard.at(i).at(j);
            if (piece != nullptr && piece->getColor() == other && (piece->repr() == "King0" || piece->repr() == "King1")) {
                if (std::dynamic_pointer_cast<King>(piece)->getIsInCheck()) {
                    // check if king can escape a checked state by moving
                    auto moves = piece->possibleMoves(i, j, *this);
                    for (const auto &mv: moves) {
                        // perform move
                        Board tmp{};
                        tmp.mainBoard = mainBoard;
                        // if performing the move lets the king escape the check, then it can perform that move
                        if (tmp.movePiece(i, j, mv.first, mv.second) && !tmp.isChecked(other)) {
                            return false;
                        }
                    }
                    // otherwise, the king can't escape the check by his own
                }
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (mainBoard.at(i).at(j) != nullptr && mainBoard.at(i).at(j)->getColor() == other) {
                // check if another piece can help him
                auto piece = mainBoard.at(i).at(j);
                auto moves = piece->possibleMoves(i, j, *this);
                for (const auto &mv: moves) {
                    // perform move
                    Board tmp{};
                    tmp.mainBoard = mainBoard;
                    // if performing the move lets the king escape the check, then it can perform that move
                    if (tmp.movePiece(i, j, mv.first, mv.second) && !tmp.isChecked(other)) {
                        return false;
                    }
                    // add positions of the pieces who can safe the king
                }
            }
        }
    }

    return true;
}

bool chess::Board::isStaleMate(const chess::Color &color) {
    Color other;
    if (color == WHITE) {
        other = BLACK;
    } else {
        other = WHITE;
    }
    if (!isChecked(other)) {
        int countPieces = 0;
        int countPiecesCantMove = 0;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (mainBoard.at(i).at(j) != nullptr && mainBoard.at(i).at(j)->getColor() == other) {
                    auto piece = mainBoard.at(i).at(j);
                    auto moves = piece->possibleMoves(i, j, *this);
                    if (moves.empty()) {
                        countPiecesCantMove++;
                    }
                }
            }
        }
        if (countPieces == countPiecesCantMove) {
            return true;
        }
    }
    return false;
}

chess::BoardType &chess::Board::getBoardData() {
    return mainBoard;
}

