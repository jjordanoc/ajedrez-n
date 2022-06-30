#include "Play.h"

Play::Play() {
    boardTexture.loadFromFile("../../src/frontend/assets/textures/board.png");
    boardSprite.setTexture(&boardTexture);
    engine.initBoard();
    drawBoard();
}

void Play::drawBoard() {
    boardSprite.setSize(sf::Vector2f(600, 600));
    float boardX = windowWidth/2.0 - 600/2.0;
    float boardY = windowHeight/2.0 - 600/2.0;
    boardSprite.setPosition(boardX, boardY);

    /*
     * Posiciones de las piezas respecto dentro del tablero

     (0, 0)      (75, 75),   (150, 150),   (225, 225),   (300, 300),   (375, 375),   (450, 450),   (525, 525)
     * */

    /*
     * Posiciones de las piezas en la pantalla:
     * A la x de la pieza le sumamos boardX
     * A la y de la pieza le sumamos boardY
     */
}

void Play::piecePressed(double windowX, double windowY) {
    int col, row;
    if (boardX <= windowX <= boardX+600) {
        col = (windowX - boardX) / 75.0;
        row = (windowY - boardY) / 75.0;

        auto currentBoard = engine.getBoard().getBoardData();
        auto currentPiece = currentBoard.at(row).at(col);

        if (currentPiece != nullptr) {
            for (auto c: currentPiece->possibleMoves(row, col, engine.getBoard())) {
                possibleMoves.push_back({c.second * 75.0 + boardX, c.first * 75.0 + boardY});
                cout << c.first << " " << c.second << endl;
            }
        }
    }



//    currentBoard.movePiece(row, col);
//    currentBoard->movePiece(row, col, newRow, newCol);



/*    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = currentBoard.at(i).at(j);
            if (piece != nullptr) {

            }
        }
    }*/
}

void Play::handleEvents(sf::RenderWindow &window) {
    inCurrentState = true;
    sf::Event event{};

    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        inCurrentState = false;
                        break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                piecePressed(event.mouseButton.x, event.mouseButton.y);
                break;
        }
    }
}

void Play::render(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);
    draw(window);
    window.display();
}

void Play::draw(sf::RenderWindow &window) {
    auto currentBoard = engine.getBoard().getBoardData();
    window.draw(boardSprite);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = currentBoard.at(i).at(j);
            if (piece != nullptr) {
                piece->drawPiece(window, i, j);
            }
        }
    }
}

void Play::update(sf::RenderWindow &window, int &currentState) {
    if (!inCurrentState) currentState = 1;
}

Play::~Play() = default;
