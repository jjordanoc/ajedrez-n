//
// Created by renato on 6/21/2022.
//

#ifndef PROYECTO_AI_H
#define PROYECTO_AI_H

#include "Board.h"
#include "../global/Global.h"

namespace chess {

    // Minimax algorithm
    class AI {
        Color color = BLACK;
        int depthLimit = 5;
    public:
        AI();
        AI(Color color, int depthLimit);
        ScoreType minimax(chess::Board &table, bool playMax, int depth);
        ScoreType alphaBetaPrunedMinimax(chess::Board &table, bool playMax, ScoreType alpha = MIN_SCORE, ScoreType beta = MAX_SCORE, int depth = 0);
        void move(chess::Board &table);
        Color getColor();
    };
}// namespace chess


#endif//PROYECTO_AI_H
