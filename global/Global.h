#ifndef PROYECTO_GLOBAL_H
#define PROYECTO_GLOBAL_H

#include <string>

#define BOARD_SIZE 8
#define PIECES {"King", "Queen", "Knight", "Pawn", "Rook", "Bishop"}



namespace chess {
    typedef unsigned short PosType;
    enum Color {
        BLACK,
        WHITE
    };

}


#endif//PROYECTO_GLOBAL_H
