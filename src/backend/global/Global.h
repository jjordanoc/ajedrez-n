#ifndef PROYECTO_GLOBAL_H
#define PROYECTO_GLOBAL_H

#include <string>

#define BOARD_SIZE 8
#define MAX_SCORE 99999999
#define MIN_SCORE -MAX_SCORE
#define CHECK_VALUE 200


namespace chess {
    typedef unsigned short PosType;
    typedef long long ScoreType;
    enum Color {
        BLACK,
        WHITE
    };
}


#endif//PROYECTO_GLOBAL_H
