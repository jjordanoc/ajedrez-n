#include "Engine.h"
#include <cmath>

chess::Engine::Engine() : board(std::make_unique<Board>()), turn(chess::WHITE) {
}

chess::Engine &chess::Engine::getInstance() {
    static Engine instance;
    return instance;
}

void chess::Engine::initBoard(int n) {
    // Initialize an empty board
    for (unsigned long long i = 0; i < BOARD_SIZE; ++i) {
        for (unsigned long long j = 0; j < BOARD_SIZE; ++j) {
            board->getBoardData().at(i).at(j) = nullptr;
        }
    }

    // Initialize the board base on the parameter n

    // Initialize the base board
    classicGame();
    if (n == 0) {
        return;
    }

    if (n % 9 == 0) {
        std::cout << n << std::endl;
        std::cout << std::log(n) / std::log(9) << std::endl;
        auto value = std::ceil((std::log(n) / std::log(9)) * std::abs(std::cos(n)));
        std::cout << value;
        if (value > BOARD_SIZE) {
            value = BOARD_SIZE;
        }

        for (int i = 0; i < value; i++) {
            board->putPiece("Queen", Color::WHITE, 6, i);
        }

        for (int i = 0; i < value; i++) {
            board->putPiece("Queen", Color::BLACK, 1, i);
        }
    }
    //    n % 9 == 0, ceil(log9(n) *|cos(n)|) peones se vuelven reinas.
}

void chess::Engine::nextTurn() {
    if (turn == BLACK) {
        turn = WHITE;
    } else {
        turn = BLACK;
    }
}

chess::GameState chess::Engine::getWinner() const { return winner; }

bool chess::Engine::isGameOver() const {
    return winner != chess::IN_GAME;
}

void chess::Engine::checkState() {

    if (board->isCheckMate(chess::WHITE)) {
        winner = chess::WHITE_WINS;
    } else if (board->isCheckMate(chess::BLACK)) {
        winner = chess::BLACK_WINS;
    }

    if (board->isStaleMate(chess::WHITE) || board->isStaleMate(chess::BLACK) || board->fiftyMoveDraw()) {
        winner = chess::DRAW;
    }
}

chess::Board &chess::Engine::getBoard() {
    return *board;
}
chess::Color chess::Engine::getTurn() {
    return turn;
}
void chess::Engine::forceGameOver() {
    winner = chess::DRAW;
}
