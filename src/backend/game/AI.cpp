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
                        perf += 1;
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
                        perf += 1;
                        best_value = std::min(best_value, minimax(tmp, true, depth += 1));
                    }
                }
            }
        }
        return best_value;
    }
}


chess::ScoreType chess::AI::alphaBetaPrunedMinimax(chess::Board &table, bool playMax, ScoreType alpha, ScoreType beta, int depth) {
    // ejemplo: playmax inicia en negro
    perf += 1;
    ScoreType score = table.evaluation();                                 // evaluar tablero actual
    if (score == MAX_SCORE || score == MIN_SCORE || depthLimit <= depth) {// si el score es el de un jaque mate o llegamos a la profundidad maxima permitida, retornar el puntaje
        return score;
    }
    if (playMax) {// falso, pues inicia el negro
        ScoreType maxEvaluation = MIN_SCORE;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (table.getPiece(i, j) != nullptr && table.getPiece(i, j)->getColor() == chess::WHITE) {
                    auto piece = table.getPiece(i, j);
                    auto possibleMoves = piece->possibleMoves(i, j, table);
                    for (auto &move: possibleMoves) {
                        chess::Board tmp = chess::Board(table);
                        tmp.movePiece(i, j, move.first, move.second);
                        auto evaluation = alphaBetaPrunedMinimax(tmp, false, alpha, beta, depth += 1);
                        maxEvaluation = std::max(maxEvaluation, evaluation);
                        alpha = std::max(alpha, evaluation);
                        if (beta <= alpha) {
                            return maxEvaluation;
                        }
                    }
                }
            }
        }
        return maxEvaluation;
    } else {
        ScoreType minEvaluation = MAX_SCORE;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (table.getPiece(i, j) != nullptr && table.getPiece(i, j)->getColor() == chess::BLACK) {
                    auto piece = table.getPiece(i, j);                     // obtener la pieza en la posicion
                    auto possibleMoves = piece->possibleMoves(i, j, table);// ver sus posibles movimientos
                    for (auto &move: possibleMoves) {                      // para cada posible movimiento de cada pieza
                        chess::Board tmp = chess::Board(table);
                        tmp.movePiece(i, j, move.first, move.second);
                        auto evaluation = alphaBetaPrunedMinimax(tmp, true, alpha, beta, depth += 1);
                        minEvaluation = std::min(minEvaluation, evaluation);
                        beta = std::min(beta, evaluation);
                        if (beta <= alpha) {
                            return minEvaluation;
                        }
                    }
                }
            }
        }
        return minEvaluation;
    }
}


void chess::AI::move(chess::Board &table) {
    ScoreType bestScore = MAX_SCORE;
    auto bestMove = std::make_pair(0, 0);
    auto bestPos = std::make_pair(0, 0);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = table.getPiece(i, j);
            if (piece != nullptr && piece->getColor() == color) {
                auto possibleMoves = piece->possibleMoves(i, j, table);// posibles movimientos de la pieza
                for (const auto &e: possibleMoves) {                   // para cada posible movimiento
                    chess::Board tmp = chess::Board(table);            // crear un tablero alternativo
                    tmp.move(i, j, e.first, e.second);                 // hacer el movimiento en un tablero a parte (subarbol)
                    auto score = alphaBetaPrunedMinimax(tmp, true);    // evaluar el movimiento mediante minimax con alpha-beta pruning
                    perf += 1;                                         // contar los nodos del arbol para su posterior validacion
                    if (score < bestScore) {
                        bestScore = score;
                        bestMove = std::make_pair(e.first, e.second);
                        bestPos = std::make_pair(i, j);
                    }
                }
            }
        }
    }
    table.move(bestPos.first, bestPos.second, bestMove.first, bestMove.second);// realizar el mejor movimiento desde la mejor posicion
}
chess::Color chess::AI::getColor() {
    return color;
}

unsigned long long chess::AI::getPerf() const { return perf; }
