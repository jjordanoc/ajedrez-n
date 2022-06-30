#ifndef PROYECTO_ENGINE_H
#define PROYECTO_ENGINE_H
#include "Board.h"
#include "Player.h"

namespace chess {

    class Engine {
        std::unique_ptr<Player> player1;
        std::unique_ptr<Player> player2;
        std::unique_ptr<Board> board;
        Color turn;
        unsigned long long n = 0;
        inline static Engine *instance = nullptr;
        Engine();
    public:
        static Engine &getInstance();
        void initBoard();
        void testGame();
        void nextTurn();
        Board& getBoard();
        unsigned long long Perft(int depth);
        ~Engine();
    };

}// namespace chess


#endif//PROYECTO_ENGINE_H
