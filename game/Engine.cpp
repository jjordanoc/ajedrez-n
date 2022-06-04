#include "Engine.h"

chess::Engine::Engine() : board(std::make_unique<Board>()), player1(std::make_unique<Player>(BLACK)), player2(std::make_unique<Player>(WHITE)) {
}

void chess::Engine::initBoard(){
    // generar reglas del juego en base al n

    // si n es 0, se crea el juego base

    // se crea el tablero

    board->putPiece("King", Color::WHITE, 7, 3);
    board->putPiece("King", Color::BLACK, 0, 3);

    board->putPiece("Queen", Color::WHITE, 7, 4);
    board->putPiece("Queen", Color::BLACK, 0, 4);

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


    for(int i = 0; i < BOARD_SIZE; i++){
        board->putPiece("Pawn", Color::WHITE, 6, i);
    }

    for(int i = 0; i < BOARD_SIZE; i++){
        board->putPiece("Pawn", Color::BLACK, 1, i);
    }
}
void chess::Engine::initGame() {

    // Probamos si podemos seleccionar alguna pieza
    board->print();
    while (true) {
        int row=0, col=0, newRow=0, newCol=0;
        std::cout << "Ingrese una fila y columna para seleccionar una pieza: " << std::endl;
        std::cin >> row >> col;
        if(player1->getColor() == board->getPiece(row, col)->getColor()){
            std::vector<std::pair<PosType, PosType>> vec = board->getPiece(row, col)->possibleMoves(row, col, board->getBoardData());
            // agregar mas restricciones
            for(const auto& e : vec){
                std::cout << "Posibles movimientos: " << std::endl;
                std::cout << e.first << " " << e.second << std::endl;
            }
            if (!vec.empty()) {
                std::cout << "Ingrese una fila y columna para moverte: " << std::endl;
                std::cin >> newRow >> newCol;
                if (newRow == -1 || newCol == -1) {
                    break;
                }
                board->movePiece(row, col, newRow, newCol);
            }
        } else {
            std::cout << "Esta no es tu pieza!!!" << std::endl;
        }

        board->print();
    }
}
