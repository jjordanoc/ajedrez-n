#include "Engine.h"

chess::Engine::Engine() : board(std::make_unique<Board>()), player1(std::make_unique<Player>(BLACK)),
                          player2(std::make_unique<Player>(WHITE)), turn(chess::WHITE) {
}

void chess::Engine::initBoard() {
    // generar reglas del juego en base al n

    // si n es 0, se crea el juego base

    // se crea el tablero

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

void chess::Engine::initGame() {
    // Probamos si podemos seleccionar alguna pieza
    board->print();
    while (true) {
        if (board->isStaleMate(chess::WHITE) || board->isStaleMate(chess::BLACK) || board->fiftyMoveDraw()) {
            std::cout << "IT'S A DRAW :D" << std::endl;
            return;
        }
        if (board->isCheckMate(chess::WHITE)){
            std::cout << "WHITE WON :D" << std::endl;
            return;
        } else if(board->isCheckMate(chess::BLACK)) {
            std::cout << "BLACK WON :D" << std::endl;
            return;
        } else {
            std::cout << "IT IS " << turn << "'S TURN" << std::endl;
            int row = 0, col = 0, newRow = 0, newCol = 0;
            std::cout << "SELECT A PIECE (EX: 0 1): " << std::endl;
            std::cin >> row >> col;
            if (row == -1 || col == -1) {
                return;
            }
            if (board->getPiece(row, col) == nullptr) {
                continue;
            }
            if (turn == WHITE && board->isChecked(chess::WHITE)) {
                std::cout << "WHITE IS CHECKED!" << std::endl;
            }
            if (turn == BLACK && board->isChecked(chess::BLACK)) {
                std::cout << "BLACK IS CHECKED!" << std::endl;
            }
            if (turn == board->getPiece(row, col)->getColor()) {
                std::vector<std::pair<PosType, PosType>> vec = board->getPiece(row, col)->possibleMoves(row, col, *board);

                for (const auto &e: vec) {
                    std::cout << "POSSIBLE MOVE: " << std::endl;
                    std::cout << e.first << " " << e.second << std::endl;
                }
                if (!vec.empty()) {
                    do{
                        std::cout << "SELECT A MOVE (EX: 0 1): " << std::endl;
                        std::cin >> newRow >> newCol;
                        if (newRow == -1 || newCol == -1) {
                            return;
                        }
                    } while ( std::find(begin(vec), end(vec), std::pair<PosType, PosType>(newRow, newCol)) == end(vec) );
                    board->checkCastling(row, col, newRow, newCol);
                    board->getPiece(row, col)->incrementMoveCount();
                    board->movePiece(row, col, newRow, newCol);
                    board->checkPawnPromotion(newRow, newCol);
                    nextTurn();
                }
            } else {
                std::cout << "YOU CAN'T MOVE THIS PIECE" << std::endl;
            }
            board->print();
        }
    }
}

chess::Engine *chess::Engine::get_instance() {
    if (instance == nullptr) {
        instance = new Engine();
    }
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
