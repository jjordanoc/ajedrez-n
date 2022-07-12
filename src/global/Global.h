#ifndef PROYECTO_GLOBAL_H
#define PROYECTO_GLOBAL_H

#include <string>

#define BOARD_SIZE 8

#define MAX_SCORE 99999999
#define MIN_SCORE -MAX_SCORE

#define AI_DEPTH 5

#define CHECK_VALUE 200
#define QUEEN_VALUE 1200
#define ROOK_VALUE 700
#define KNIGHT_VALUE 500
#define BISHOP_VALUE 400
#define PAWN_VALUE 100

#define PAWN_CENTER_CONTROL_VALUE 50

#define BEST_OPENING_VALUE 300


namespace chess {
    typedef unsigned short PosType;
    typedef long long ScoreType;
    enum Color {
        BLACK,
        WHITE
    };
    enum GameState {
        BLACK_WINS,
        WHITE_WINS,
        DRAW,
        IN_GAME
    };
}// namespace chess


#endif//PROYECTO_GLOBAL_H
