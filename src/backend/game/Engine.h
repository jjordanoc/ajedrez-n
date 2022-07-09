#ifndef PROYECTO_ENGINE_H
#define PROYECTO_ENGINE_H
#include "Board.h"

namespace chess {

    class Engine {
        std::unique_ptr<Board> board;
        Color turn;
        unsigned long long n = 0;

    public:
        Engine();
        static Engine &getInstance();
        void initBoard();
        void nextTurn();
        Board& getBoard();
        Color getTurn();
        void playerMove(PosType oldRow, PosType oldCol, PosType newRow, PosType newCol);
        ~Engine();
    };

}// namespace chess


#endif//PROYECTO_ENGINE_H
