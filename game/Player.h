#ifndef PROYECTO_PLAYER_H
#define PROYECTO_PLAYER_H

#include "../global/Global.h"

namespace chess{
    class Player {
        Color color;
    public:
        Player(Color color):color(color){}
        Color getColor(){return color;}

    };
}



#endif//PROYECTO_PLAYER_H
