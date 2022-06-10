#include "King.h"
#include "../game/Board.h"

chess::King::King(const Color &color) : Piece(color) {
}

std::string chess::King::repr() {
    return "King" + std::to_string(color);
}
void chess::King::setIsInCheck(bool i) {
    isChecked = i;
}
bool chess::King::getIsInCheck() const {
    return isChecked;
}
std::vector<std::pair<chess::PosType, chess::PosType>> chess::King::possibleMoves(chess::PosType fromRow, chess::PosType fromCol, Board& currentBoard) {
    auto boardData = currentBoard.getBoardData();
    std::vector<std::pair<PosType, PosType>> moves;
    for (int i = -1; i <= 1; i += 1) {
        for (int j = -1; j <= 1; j += 1) {
            if (i == 0 && j == 0) {
                continue;
            }
            if(inBounds(fromRow + i, fromCol + j)){
                if(boardData.at(fromRow + i).at(fromCol + j) != nullptr){
                    if(boardData.at(fromRow + i).at(fromCol + j)->getColor() != color){
                        if(boardData.at(fromRow + i).at(fromCol + j)->repr() != "King0" &&
                            boardData.at(fromRow + i).at(fromCol + j)->repr() != "King1"){
                            // check if potential move actually puts king in a check state
                            Board tmp(currentBoard);
                            if (tmp.movePiece(fromRow, fromCol, fromRow+i, fromCol+j) && !tmp.isChecked(color)) {
                                moves.emplace_back(fromRow + i, fromCol + j);
                            }
                        }
                    }
                } else {
                    // check if potential move actually puts king in a check state
                    Board tmp(currentBoard);
                    if (tmp.movePiece(fromRow, fromCol, fromRow+i, fromCol+j) && !tmp.isChecked(color)) {
                        moves.emplace_back(fromRow + i, fromCol + j);
                    }
                    moves.emplace_back(fromRow + i, fromCol + j);
                }
            }
        }
    }

    // Castling's logic
    // Check if king has moved
    if (!hasMoved && !isChecked) {
        if (color == BLACK) {
            // Check long Castling
            // Check if the nearest rook has moved
            if (boardData.at(0).at(0) != nullptr &&
                boardData.at(0).at(1) == nullptr &&
                boardData.at(0).at(2) == nullptr &&
                boardData.at(0).at(3) == nullptr) {
                auto farthest_rook = boardData.at(0).at(0);
                if (farthest_rook->getColor() == BLACK) {
                    if (!farthest_rook->getHasMoved()) {
                        moves.emplace_back(0, 2);
                    }
                }
            }

            // Check short Castling
            // Check if the farthest rook has moved
            if (boardData.at(0).at(7) != nullptr &&
                boardData.at(0).at(6) == nullptr &&
                boardData.at(0).at(5) == nullptr) {
                auto nearest_rook = boardData.at(0).at(7);
                if (nearest_rook->getColor() == BLACK) {
                    if (!nearest_rook->getHasMoved()) {
                        moves.emplace_back(0, 6);
                    }
                }
            }
        } else if (color == WHITE) {
            // Check long Castling
            // Check if the nearest rook has moved
            if (boardData.at(7).at(0) != nullptr &&
                boardData.at(7).at(1) == nullptr &&
                boardData.at(7).at(2) == nullptr &&
                boardData.at(7).at(3) == nullptr) {
                auto farthest_rook = boardData.at(7).at(0);
                if (farthest_rook->getColor() == WHITE) {
                    if (!farthest_rook->getHasMoved()) {
                        moves.emplace_back(7, 2);
                    }
                }
            }

            // Check short Castling
            // Check if the farthest rook has moved
            if (boardData.at(7).at(7) != nullptr &&
                boardData.at(7).at(6) == nullptr &&
                boardData.at(7).at(5) == nullptr) {
                auto nearest_rook = boardData.at(7).at(7);
                if (nearest_rook->getColor() == WHITE) {
                    if (!nearest_rook->getHasMoved()) {
                        moves.emplace_back(7, 6);
                    }
                }
            }
        }
    }

    // Checkmate's logic
    if (color == BLACK) {
        // Check Short Castling
        // Check if the nearest rook has moved
        if (boardData.at(0).at(0) != nullptr &&
            boardData.at(0).at(1) == nullptr &&
            boardData.at(0).at(2) == nullptr) {
            auto nearest_rook = boardData.at(0).at(0);
            if (nearest_rook->getColor() == BLACK) {
                if (!nearest_rook->getHasMoved()) {
                    moves.emplace_back(0, 1);
                }
            }
        }

        // Check Long Castling
        // Check if the farthest rook has moved
        if (boardData.at(0).at(7) != nullptr &&
            boardData.at(0).at(6) == nullptr &&
            boardData.at(0).at(5) == nullptr &&
            boardData.at(0).at(4) == nullptr) {
            auto farthest_rook = boardData.at(0).at(7);
            if (farthest_rook->getColor() == BLACK) {
                if (!farthest_rook->getHasMoved()) {
                    moves.emplace_back(0, 5);
                }
            }
        }
    }


    return moves;
}

