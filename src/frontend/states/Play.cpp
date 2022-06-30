#include "Play.h"

Play::Play() {
    boardTexture.loadFromFile("../../src/frontend/assets/textures/board.png");
    boardSprite.setTexture(&boardTexture);

    for (int i = 0; i < 32; ++i)
        f[i].setTexture(piecesTexture);

    cargarPosicion();
}

void Play::cargarTablero() {
    boardSprite.setSize(sf::Vector2f(600, 600));
    float boardX = windowWidth/2.0 - 600/2.0;
    float boardY = windowHeight/2.0 - 600/2.0;
    boardSprite.setPosition(boardX, boardY);

    int k = 0;
    for (int i = 0; i < 8; ++i){
        for (int j = 0 ; j < 8; ++j){
            int n = board[i][j];
            if(!n)
                continue;
            int x = abs(n) - 1;
            int y = n > 0 ? 1 : 0;
            f[k].setTextureRect( sf::IntRect(sz*x, sz*y , sz, sz));
            f[k].setScale(1.2, 1.2);
            f[k].setPosition(sz*1.25*j + boardX, sz*1.25*i + boardY);
            ++k;
        }
    }
}

void Play::handleEvents(sf::RenderWindow &window) {
    inCurrentState = true;
    sf::Event event{};

    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        inCurrentState = false;
                        break;
                }
        }
    }
}



void Play::render(sf::RenderWindow &window) {
    window.clear(sf::Color::Black);
    draw(window);
    window.display();

    //
    auto currentBoard = engine.getBoard().getBoardData();
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = currentBoard.at(i).at(j);
            if (piece != nullptr) {
                piece->drawPiece(window, i, j);
            }
        }
    }
}

void Play::draw(sf::RenderWindow &window) {
    window.draw(boardSprite);
    for (int i = 0; i < 32; ++i)
        window.draw(f[i]);
}

void Play::update(sf::RenderWindow &window, int &currentState) {
    if (!inCurrentState) currentState = 1;
}

Play::~Play() = default;
