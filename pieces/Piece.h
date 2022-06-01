#ifndef PROYECTO_PIECE_H
#define PROYECTO_PIECE_H

#include <iostream>
#include "PieceFactory.h"


class Piece {
protected:
    Color color;
    std::pair<int, int> position;
    int value = 0;
public:
    virtual std::string repr() = 0;
};


#endif
