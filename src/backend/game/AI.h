//
// Created by renato on 6/21/2022.
//

#ifndef PROYECTO_AI_H
#define PROYECTO_AI_H

#include "Board.h"

namespace chess {

    // Minimax algorithm
    double minimax(chess::Board &table, bool playMax, int depthLimit, int depth = 0);
}// namespace chess


#endif//PROYECTO_AI_H
