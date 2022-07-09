#ifndef PROYECTO_ENGINE_H
#define PROYECTO_ENGINE_H
#include "Board.h"

namespace chess {

    class Engine {
        std::unique_ptr<Board> board;
        Color turn;
        GameState winner = IN_GAME;
        Engine();
    public:
        static Engine &getInstance();
        void initBoard(int n);
        void nextTurn();
        Board &getBoard();
        Color getTurn();
        GameState getWinner() const;
        void forceGameOver();
        bool isGameOver() const;
        void checkState();
    };

}// namespace chess


#endif//PROYECTO_ENGINE_H
