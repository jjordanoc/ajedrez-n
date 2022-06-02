#ifndef PROYECTO_ENGINE_H
#define PROYECTO_ENGINE_H
#include "Board.h"
#include "Player.h"

namespace chess {

    class Engine {
        std::unique_ptr<Player> player1;
        std::unique_ptr<Player> player2;
        std::unique_ptr<Board> board;
        unsigned long long n = 0;
    public:
        Engine();
        void initBoard();
        void initGame();
    };

}// namespace chess


#endif//PROYECTO_ENGINE_H
