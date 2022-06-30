//
// Created by renato on 6/21/2022.
//

#include "AI.h"
double chess::minimax(chess::Board &table, bool playMax, int depthLimit, int depth) {
    double score = table.evaluation();
    if (score == std::numeric_limits<double>::infinity() || score == -std::numeric_limits<double>::infinity() || depthLimit <= depth) {
        return score;
    }
    if (playMax) {
        double best_value = -std::numeric_limits<double>::infinity();
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {

                if (table.getPiece(i, j) != nullptr && table.getPiece(i, j)->getColor() == chess::WHITE) {
                    auto piece = table.getPiece(i, j);
                    auto possibleMoves = piece->possibleMoves(i, j, table);
                    for (auto &move: possibleMoves) {
                        table.movePiece(i, j, move.first, move.second);
                        best_value = std::max(best_value, minimax(table, false, depthLimit, depth += 1));
                        table.movePiece(move.first, move.second, i, j);
                    }
                }
            }
        }
        return best_value;
    } else {
        double best_value = std::numeric_limits<double>::infinity();
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (table.getPiece(i, j) != nullptr && table.getPiece(i, j)->getColor() == chess::BLACK) {
                    auto piece = table.getPiece(i, j);
                    auto possibleMoves = piece->possibleMoves(i, j, table);
                    for (auto &move: possibleMoves) {
                        table.movePiece(i, j, move.first, move.second);
                        best_value = std::min(best_value, minimax(table, true, depthLimit, depth += 1));
                        table.movePiece(move.first, move.second, i, j);
                    }
                }
            }
        }
        return best_value;
    }
}
