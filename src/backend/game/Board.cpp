#include "Board.h"
#include <cmath>


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
            if(king->getColor() == chess::WHITE){
                if (newCol == 2 && newRow == 7) {
                    isMakingLongCastling = true;
                    isMakingCastling = true;
                } else if (newCol == 6 && newRow == 7) {
                    isMakingShortCastling = true;
                    isMakingCastling = true;
                }
            } else if(king->getColor() == chess::WHITE) {
                if (newCol == 2 && newRow == 0) {
                    isMakingLongCastling = true;
                    isMakingCastling = true;
                } else if (newCol == 6 && newRow == 0) {
                    isMakingShortCastling = true;
                    isMakingCastling = true;
                }
            }

        }
    }
}

void chess::Board::checkEnPassant(PosType oldRow, PosType oldCol, PosType newRow, PosType newCol) {
    auto pawn = std::dynamic_pointer_cast<Pawn>(mainBoard.at(oldRow).at(oldCol));
    if (pawn != nullptr) {
        short off = mainBoard.at(oldRow).at(oldCol)->getColor() == BLACK ? 1 : -1;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                auto piece = std::dynamic_pointer_cast<Pawn>(mainBoard.at(i).at(j));
                if (piece != nullptr && piece->getIsEnPassant()) {
                    if (newRow == i + off && newCol == j) {
                        isMakingEnPassant = true;
                    }
                }
            }
        }
    }
}


bool chess::Board::movePiece(PosType oldRow, PosType oldCol, PosType newRow, PosType newCol) {
    if (std::dynamic_pointer_cast<Pawn>(mainBoard.at(oldRow).at(oldCol)) != nullptr && abs(newRow - oldRow) == 2) {
        std::dynamic_pointer_cast<Pawn>(mainBoard.at(oldRow).at(oldCol))->setIsEnPassant(true);
    }

    if (std::dynamic_pointer_cast<Pawn>(mainBoard.at(oldRow).at(oldCol)) == nullptr &&
        mainBoard.at(newRow).at(newCol) == nullptr) {
        fiftyMoveCount++;
    } else {
        fiftyMoveCount = 0;
    }

    if (isMakingCastling) {
        // We move 2 pieces, the king and the rook
        auto king = mainBoard.at(oldRow).at(oldCol);

        if (isMakingShortCastling) {
            if (king->getColor() == BLACK) {
                mainBoard.at(0).at(5) = std::move(mainBoard.at(0).at(7));
                mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
            } else {
                mainBoard.at(7).at(5) = std::move(mainBoard.at(7).at(7));
                mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
            }
        } else if (isMakingLongCastling) {
            if (king->getColor() == BLACK) {
                mainBoard.at(0).at(3) = std::move(mainBoard.at(0).at(0));
                mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
            } else {
                mainBoard.at(7).at(3) = std::move(mainBoard.at(7).at(0));
                mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
            }
        }
        isMakingCastling = false;
        isMakingLongCastling = false;
        isMakingShortCastling = false;
        return true;
    }

    if (isMakingEnPassant) {
        short off = mainBoard.at(oldRow).at(oldCol)->getColor() == BLACK ? 1 : -1;
        mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
        mainBoard.at(newRow - off).at(newCol) = nullptr;
        isMakingEnPassant = false;
        return true;
    }

    if (mainBoard.at(newRow).at(newCol) == nullptr) {
        mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));

        return true;
    } else if (mainBoard.at(newRow).at(newCol)->repr() != "King0" &&
               mainBoard.at(newRow).at(newCol)->repr() != "King1") {
        mainBoard.at(newRow).at(newCol) = std::move(mainBoard.at(oldRow).at(oldCol));
        // This statement it's not necessary because we can validate the possible moves and this isn't a possible move
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

void chess::Board::putKingChecked(const chess::Color &color, bool checked) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = mainBoard.at(i).at(j);
            if (piece != nullptr) {
                if (color == BLACK) {
                    if (piece->repr() == "King0") {
                        std::dynamic_pointer_cast<King>(piece)->setIsInCheck(checked);
                    }
                } else if (color == WHITE) {
                    if (piece->repr() == "King1") {
                        std::dynamic_pointer_cast<King>(piece)->setIsInCheck(checked);
                    }
                }
            }
        }
    }
}

// Check if "color" is checked
bool chess::Board::isChecked(const chess::Color &color) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = mainBoard.at(i).at(j);
            if (piece != nullptr && piece->getColor() == getOtherColor(color)) {
                // update the piece
                piece->verifyPossibleChecks(i, j, *this);
                // check if this piece is checking the king
                if (piece->getIsCheckingKing()) {
                    putKingChecked(color, true);
                    return true;
                }
            }
        }
    }
    putKingChecked(color, false);
    return false;
}

// Return if "color" has won
bool chess::Board::isCheckMate(const Color &color) {
    if (!isChecked(getOtherColor(color))) {
        return false;
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = mainBoard.at(i).at(j);
            if (piece != nullptr && piece->getColor() == getOtherColor(color)) {
                // check if another piece can help him
                if (!(piece->possibleMoves(i, j, *this).empty())) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool chess::Board::isStaleMate(const chess::Color &color) {
    if (!isChecked(getOtherColor(color))) {
        int countPieces = 0;
        int countPiecesCantMove = 0;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                if (mainBoard.at(i).at(j) != nullptr && mainBoard.at(i).at(j)->getColor() == getOtherColor(color)) {
                    ++countPieces;
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

chess::Color chess::Board::getOtherColor(const chess::Color &color) {
    Color other;
    if (color == WHITE) {
        other = BLACK;
    } else {
        other = WHITE;
    }
    return other;
}

bool chess::Board::fiftyMoveDraw() {
    if (fiftyMoveCount == 50) {
        return true;
    }
    return false;
}

void chess::Board::deleteEnPassant() {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = std::dynamic_pointer_cast<Pawn>(mainBoard.at(i).at(j));
            if (piece != nullptr && piece->getIsEnPassant()) {
                piece->setIsEnPassant(false);
            }
        }
    }
}

chess::ScoreType chess::Board::evaluation() {
    // Evaluation of checkmate
    if(isCheckMate(BLACK)){
        return MIN_SCORE;
    } else if(isCheckMate(WHITE)){
        return MAX_SCORE;
    }
    // Evaluation of the pieces
    ScoreType blackPoints = 0;
    ScoreType whitePoints = 0;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = mainBoard.at(i).at(j);
            if (piece != nullptr) {
                if (piece->getColor() == BLACK) {
                    blackPoints += piece->getValue();
                    if (std::dynamic_pointer_cast<Pawn>(piece) != nullptr) {
                        if ((i >= BOARD_SIZE / 2 && i <= BOARD_SIZE / 2 + 1) || (j >= BOARD_SIZE / 2 && j <= BOARD_SIZE / 2 + 1)) {
                            blackPoints += 50;
                        }
                    }
                    if (std::dynamic_pointer_cast<King>(piece) != nullptr) {
                        whitePoints += (std::pow(j - BOARD_SIZE / 2, 2) - std::pow(j, 2)) * 4;
                    }
                } else {
                    whitePoints += piece->getValue();
                    if (std::dynamic_pointer_cast<Pawn>(piece) != nullptr) {
                        if ((i >= BOARD_SIZE / 2 && i <= BOARD_SIZE / 2 + 1) || (j >= BOARD_SIZE / 2 && j <= BOARD_SIZE / 2 + 1)) {
                            whitePoints += 50;
                        }
                    }
                    if (std::dynamic_pointer_cast<King>(piece) != nullptr) {
                        blackPoints += (std::pow(j - BOARD_SIZE / 2, 2) - std::pow(j, 2)) * 4;
                    }
                }
            }
        }
    }
    // If position checks, it is more valuable
    if (isChecked(BLACK)) {
        whitePoints += CHECK_VALUE;
    }
    else if (isChecked(WHITE)) {
        blackPoints += CHECK_VALUE;
    }
    // If the score is positive, white are winning
    return whitePoints - blackPoints;
}

void chess::Board::move(chess::PosType oldRow, chess::PosType oldCol, chess::PosType newRow, chess::PosType newCol) {
    checkCastling(oldRow, oldCol, newRow, newCol);
    getPiece(oldRow, oldCol)->incrementMoveCount();// ? Move piece
    checkEnPassant(oldRow, oldCol, newRow, newCol);
    deleteEnPassant();
    movePiece(oldRow, oldCol, newRow, newCol);
    checkPawnPromotion(newRow, newCol);
}
