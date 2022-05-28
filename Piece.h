#ifndef PROYECTO_PIECE_H
#define PROYECTO_PIECE_H

#include <iostream>
#include "PieceFactory.h"

using namespace std;



class Piece {
    Color color;
public:
    virtual string repr() = 0;
};


#endif //PROYECTO_PIECE_H
