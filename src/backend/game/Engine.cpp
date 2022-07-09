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
    std::cout << "Este es n: " << n << std::endl;
    board->setN(n);

    //    Initialize the board base on the parameter n
    //    n == 0, modo de juego clásico.
    //    n % 2 == 0, ceil(log(n)) peones pueden comer de frente.
    //    n % 4 == 0, ceil(log4(n)) peones pueden retroceder.
    //    n % 5 == 0, los reyes pueden moverse como alfiles.
    //    n % 6 == 0, ceil(log7(n)) peones pueden moverse como reyes.
    //    n % 7 == 0, Cada ceil(log7(n)) turnos, una pieza es removida.
    //    n % 8 == 0, los caballos pueden hacer 2 movimientos seguidos.

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

void chess::Engine::classicGame() {
    board->putPiece("King", Color::WHITE, 7, 4);
    board->putPiece("King", Color::BLACK, 0, 4);

    board->putPiece("Queen", Color::WHITE, 7, 3);
    board->putPiece("Queen", Color::BLACK, 0, 3);

    board->putPiece("Rook", Color::WHITE, 7, 0);
    board->putPiece("Rook", Color::WHITE, 7, 7);
    board->putPiece("Rook", Color::BLACK, 0, 0);
    board->putPiece("Rook", Color::BLACK, 0, 7);

    board->putPiece("Knight", Color::WHITE, 7, 1);
    board->putPiece("Knight", Color::WHITE, 7, 6);
    board->putPiece("Knight", Color::BLACK, 0, 1);
    board->putPiece("Knight", Color::BLACK, 0, 6);

    board->putPiece("Bishop", Color::WHITE, 7, 2);
    board->putPiece("Bishop", Color::WHITE, 7, 5);
    board->putPiece("Bishop", Color::BLACK, 0, 2);
    board->putPiece("Bishop", Color::BLACK, 0, 5);


    for (int i = 0; i < BOARD_SIZE; i++) {
        board->putPiece("Pawn", Color::WHITE, 6, i);
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        board->putPiece("Pawn", Color::BLACK, 1, i);
    }
}