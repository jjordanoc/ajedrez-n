#include "Play.h"

Play::Play() {
    boardTexture.loadFromFile("../../src/frontend/assets/textures/board.png");
    boardSprite.setTexture(&boardTexture);
    cargarTablero();
}

void Play::cargarTablero() {
    boardSprite.setSize(sf::Vector2f(600, 600));
    float boardX = windowWidth/2.0 - 600/2.0;
    float boardY = windowHeight/2.0 - 600/2.0;
    boardSprite.setPosition(boardX, boardY);


    /*
     0      75,   150,   225,   300,   375,   450,   525
     75
     150
     225
     300
     375
     450
     525
     * */
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
}

void Play::update(sf::RenderWindow &window, int &currentState) {
    if (!inCurrentState) currentState = 1;
}

Play::~Play() = default;
