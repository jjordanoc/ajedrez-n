//
// Created by renato on 6/21/2022.
//

#include "AI.h"


chess::AI::AI() = default;

chess::AI::AI(chess::Color color, int depthLimit) : color(color), depthLimit(depthLimit) {}

chess::ScoreType chess::AI::minimax(chess::Board &table, bool playMax, int depth = 0) {
    ScoreType score = table.evaluation();
    if (score >= MAX_SCORE || score <= MIN_SCORE || depthLimit <= depth) {
        return score;
    }
    if (playMax) {
        ScoreType best_value = MIN_SCORE;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {

                if (table.getPiece(i, j) != nullptr && table.getPiece(i, j)->getColor() == chess::WHITE) {
                    auto piece = table.getPiece(i, j);
                    auto possibleMoves = piece->possibleMoves(i, j, table);
                    for (auto &move: possibleMoves) {
                        chess::Board tmp = chess::Board(table);
                        tmp.movePiece(i, j, move.first, move.second);
                        best_value = std::max(best_value, minimax(tmp, false, depth += 1));
                    }
                }
            }
        }
        return best_value;
    } else {
        ScoreType best_value = MAX_SCORE;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (table.getPiece(i, j) != nullptr && table.getPiece(i, j)->getColor() == chess::BLACK) {
                    auto piece = table.getPiece(i, j);
                    auto possibleMoves = piece->possibleMoves(i, j, table);
                    for (auto &move: possibleMoves) {
                        chess::Board tmp = chess::Board(table);
                        tmp.movePiece(i, j, move.first, move.second);
                        best_value = std::min(best_value, minimax(tmp, true, depth += 1));
                    }
                }
            }
        }
        return best_value;
    }
}

void chess::AI::move(chess::Board &table) {
    bool playMax = color == WHITE;
    ScoreType bestScore = playMax  ? MIN_SCORE : MAX_SCORE;
    auto bestMove = std::make_pair(0, 0);
    auto bestPos = std::make_pair(0, 0);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = table.getPiece(i, j);
            if (piece != nullptr && piece->getColor() == color) {
                auto possibleMoves = piece->possibleMoves(i, j, table);
                for (const auto &e: possibleMoves) {
                    chess::Board tmp = chess::Board(table);
                    // Try move
                    tmp.move(i, j, e.first, e.second);
                    auto score = minimax(tmp, playMax);
                    if (playMax) {
                        if (score > bestScore) {
                            bestScore = score;
                            bestMove = std::make_pair(e.first, e.second);
                            bestPos = std::make_pair(i, j);
                        }
                    }
                    else {
                        if (score < bestScore) {
                            bestScore = score;
                            bestMove = std::make_pair(e.first, e.second);
                            bestPos = std::make_pair(i, j);
                        }
                    }
                }
            }
        }
    }
    table.move(bestPos.first, bestPos.second, bestMove.first, bestMove.second);
}
chess::Color chess::AI::getColor() {
    return color;
}
