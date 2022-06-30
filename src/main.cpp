#include "frontend/Game.h"

void test() {
    chess::Engine &engine = chess::Engine::getInstance();
    chess::AI AI = chess::AI(chess::BLACK, 5);
    engine.initBoard();
    auto board = engine.getBoard();
    // Probamos si podemos seleccionar alguna pieza
    board.print();
    while (true) {
        if (engine.getTurn() == chess::WHITE && board.isChecked(chess::WHITE)) {
            std::cout << "WHITE IS CHECKED!" << std::endl;
        }
        if (engine.getTurn() == chess::BLACK && board.isChecked(chess::BLACK)) {
            std::cout << "BLACK IS CHECKED!" << std::endl;
        }
        if (board.isStaleMate(chess::WHITE) || board.isStaleMate(chess::BLACK) || board.fiftyMoveDraw()) {
            std::cout << "IT'S A DRAW" << std::endl;
            return;
        }
        if (board.isCheckMate(chess::WHITE)) {
            std::cout << "WHITE WON" << std::endl;
            return;
        } else if (board.isCheckMate(chess::BLACK)) {
            std::cout << "BLACK WON" << std::endl;
            return;
        }
        if (AI.getColor() != engine.getTurn()) {
            std::cout << "IT IS " << engine.getTurn() << "'S TURN" << std::endl;
            int row = 0, col = 0, newRow = 0, newCol = 0;
            do {
                std::cout << "SELECT A PIECE (EX: 0 1): " << std::endl;
                std::cin >> row >> col;
                if (row == -1 || col == -1) {
                    return;
                }
            } while (!(row >= 0 && row < 8 && col >= 0 && col < 8));

            if (board.getPiece(row, col) == nullptr) {
                continue;
            }
            if (engine.getTurn() == board.getPiece(row, col)->getColor()) {

                std::vector<std::pair<chess::PosType, chess::PosType>> vec = board.getPiece(row, col)->possibleMoves(row, col,
                                                                                                                     board);

                for (const auto &e: vec) {
                    std::cout << "POSSIBLE MOVE: " << std::endl;
                    std::cout << e.first << " " << e.second << std::endl;
                }
                if (!vec.empty()) {
                    do {
                        std::cout << "SELECT A MOVE (EX: 0 1): " << std::endl;
                        std::cin >> newRow >> newCol;
                        if (newRow == -1 || newCol == -1) {
                            return;
                        }
                    } while (std::find(begin(vec), end(vec), std::pair<chess::PosType, chess::PosType>(newRow, newCol)) == end(vec));
                    board.move(row, col, newRow, newCol);
                }
            } else {
                std::cout << "YOU CAN'T MOVE THIS PIECE" << std::endl;
            }
        } else {
            AI.move(board);
        }
        engine.nextTurn();
        board.print();
    }
}

int main() {
    auto game = Game::getInstance();
    game->run();

    return 0;
}

