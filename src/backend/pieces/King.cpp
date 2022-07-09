#include "King.h"
#include "../game/Board.h"

chess::King::King(const Color &color) : Piece(color) {
    if (color == BLACK)
        pieceTexture.loadFromFile(spriteD);
    else if (color == WHITE)
        pieceTexture.loadFromFile(spriteW);

    pieceSprite.setTexture(pieceTexture);
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
    int numChecks = 0;
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
                            addPlausibleMoves(fromRow, fromCol, fromRow+i, fromCol+j, moves, currentBoard);
                        }
                        else {
                            ++numChecks;
                        }
                    }
                } else {
                    addPlausibleMoves(fromRow, fromCol, fromRow+i, fromCol+j, moves, currentBoard);
                }
            }
        }
    }

    // Castling's logic
    // Check if king has moved
    if (moveCount == 0 && !isChecked) {
        if (color == BLACK) {
            // Check long Castling
            // Check if the farthest rook has moved
            if (boardData.at(0).at(0) != nullptr &&
                boardData.at(0).at(1) == nullptr &&
                boardData.at(0).at(2) == nullptr &&
                boardData.at(0).at(3) == nullptr &&
                !checkIsCheck(fromRow, fromCol, 0, 3, currentBoard)){
                auto farthest_rook = boardData.at(0).at(0);
                if (farthest_rook->getColor() == BLACK) {
                    if (farthest_rook->getMoveCount() == 0) {
                        addPlausibleMoves(fromRow, fromCol, 0, 2, moves, currentBoard);
                    }
                }
            }

            // Check short Castling
            // Check if the nearest rook has moved
            if (boardData.at(0).at(7) != nullptr &&
                boardData.at(0).at(6) == nullptr &&
                boardData.at(0).at(5) == nullptr &&
                !checkIsCheck(fromRow, fromCol, 0, 5, currentBoard)) {
                auto nearest_rook = boardData.at(0).at(7);
                if (nearest_rook->getColor() == BLACK) {
                    if (nearest_rook->getMoveCount() == 0) {
                        addPlausibleMoves(fromRow, fromCol, 0, 6, moves, currentBoard);
                    }
                }
            }
        } else if (color == WHITE) {
            // Check long Castling
            // Check if the farthest rook has moved
            if (boardData.at(7).at(0) != nullptr &&
                boardData.at(7).at(1) == nullptr &&
                boardData.at(7).at(2) == nullptr &&
                boardData.at(7).at(3) == nullptr &&
                !checkIsCheck(fromRow, fromCol, 7, 3, currentBoard)) {
                auto farthest_rook = boardData.at(7).at(0);
                if (farthest_rook->getColor() == WHITE) {
                    if (farthest_rook->getMoveCount() == 0) {
                        addPlausibleMoves(fromRow, fromCol, 7, 2, moves, currentBoard);
                    }
                }
            }

            // Check short Castling
            // Check if the nearest rook has moved
            if (boardData.at(7).at(7) != nullptr &&
                boardData.at(7).at(6) == nullptr &&
                boardData.at(7).at(5) == nullptr &&
                !checkIsCheck(fromRow, fromCol, 7, 5, currentBoard)) {
                auto nearest_rook = boardData.at(7).at(7);
                if (nearest_rook->getColor() == WHITE) {
                    if (nearest_rook->getMoveCount() == 0) {
                        addPlausibleMoves(fromRow, fromCol, 7, 6, moves, currentBoard);
                    }
                }
            }
        }
    }
    if (numChecks != 0) {
        isCheckingKing = true;
    }
    else {
        isCheckingKing = false;
    }
    return moves;
}
void chess::King::verifyPossibleChecks(chess::PosType fromRow, chess::PosType fromCol, chess::Board &currentBoard) {
}

bool chess::King::checkIsCheck(PosType fromRow, PosType fromCol, PosType toRow, PosType toCol, Board &currentBoard){
    Board tmp(currentBoard);
    tmp.movePiece(fromRow, fromCol, toRow, toCol);
    if (tmp.isChecked(color)) {
        return true;
    }
    return false;
}
