#include "Engine.h"

chess::Engine::Engine() : board(std::make_unique<Board>()), player1(std::make_unique<Player>(BLACK)),
                          player2(std::make_unique<Player>(WHITE)), turn(chess::WHITE) {
}

void chess::Engine::initBoard() {
    // Initialize an empty board
    for (unsigned long long i = 0; i < BOARD_SIZE; ++i) {
        for (unsigned long long j = 0; j < BOARD_SIZE; ++j) {
            board->getBoardData().at(i).at(j) = nullptr;
        }
    }

    // Initialize the board base on the parameter n

    // Initialize the base board

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

void chess::Engine::testGame() {
}

chess::Engine &chess::Engine::getInstance() {
    static Engine instance;
    return instance;
}

chess::Engine::~Engine() {
    delete instance;
}

void chess::Engine::nextTurn() {
    if (turn == BLACK) {
        turn = WHITE;
    } else {
        turn = BLACK;
    }
}

unsigned long long chess::Engine::Perft(int depth) {
    unsigned long long nodes = 0;
    if (depth == 0) {
        return 1ULL;
    }
    for (unsigned long long i = 0; i < BOARD_SIZE; ++i) {
        for (unsigned long long j = 0; j < BOARD_SIZE; ++j) {
            auto piece = board->getPiece(i, j);
            if (piece == nullptr) {
                continue;
            }
            auto moves = piece->possibleMoves(i, j, *board);
            if (!moves.empty()) {
                for (const auto &m: moves) {
                    Board tmp;
                    tmp.movePiece(i, j, m.first, m.second);
                    nodes += Perft(depth - 1);
                }
            }
        }
    }
    return nodes;
}

chess::Board &chess::Engine::getBoard() {
    return *board;
}
chess::Color chess::Engine::getTurn() {
    return turn;
}
