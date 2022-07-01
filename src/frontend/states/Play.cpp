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
}

void Play::piecePressed(sf::RenderWindow &window, double windowX, double windowY) {
    int col, row;
    if (boardX <= windowX <= boardX+600 && boardY <= windowY <= boardY+600) {
        col = (windowX - boardX) / 75.0;
        row = (windowY - boardY) / 75.0;

        auto currentBoard = engine.getBoard().getBoardData();
        auto currentPiece = currentBoard.at(row).at(col);

        int counter = 0;
        if (currentPiece != nullptr && currentPiece->getColor() == chess::WHITE) {
            if (std::size(piecesPressedSquare) == 0) {
                for (auto c: currentPiece->possibleMoves(row, col, engine.getBoard())) {
                    possibleMoves.push_back({c.second * 75.0 + boardX, c.first * 75.0 + boardY});
                }
            }
            else {
                for (auto c: currentPiece->possibleMoves(row, col, engine.getBoard())) {
                    possibleMoves.at(counter++) = {c.second * 75.0 + boardX, c.first * 75.0 + boardY};
                }
            }
        }

        counter = 0;
        if (std::size(piecesPressedSquare) == 0) {
            for (auto possibleMove: possibleMoves) {
                auto piecePressedSquare = new sf::RectangleShape{sf::Vector2f(75.f, 75.f)};
                piecePressedSquare->setFillColor(sf::Color::Blue);
                piecePressedSquare->setPosition(possibleMove.first, possibleMove.second);
                piecesPressedSquare.push_back(piecePressedSquare);
            }
        }
        else {
            for (auto possibleMove: possibleMoves) {
                auto piecePressedSquare = new sf::RectangleShape{sf::Vector2f(75.f, 75.f)};
                piecePressedSquare->setFillColor(sf::Color::Blue);
                piecePressedSquare->setPosition(possibleMove.first, possibleMove.second);
                piecesPressedSquare.at(counter++) = piecePressedSquare;
            }
        }

        piecePossibleMoveSquarePressed(window, windowX, windowY, row, col);
    }
}

void Play::piecePossibleMoveSquarePressed(sf::RenderWindow &window, double windowX, double windowY, double pieceRow, double pieceCol) {
    if (boardX <= windowX <= boardX+600 && boardY <= windowY <= boardY+600) {
        for (auto possibleMove: possibleMoves) {
            if ((possibleMove.first <= windowX && windowX <= possibleMove.first+75.0) && (possibleMove.second <= windowY && windowY <= possibleMove.second+75.0)) {
                auto board = engine.getBoard();
                int newCol = (windowX - boardX) / 75.0;
                int newRow = (windowY - boardY) / 75.0;
                cout << newRow << " " << newCol << endl;
                board.movePiece(pieceRow, pieceCol, newRow, newCol);
                board.print();
            }
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
                break;
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        inCurrentState = false;
                        break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                piecePressed(window, event.mouseButton.x, event.mouseButton.y);
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

    if (std::size(piecesPressedSquare) != 0) {
        for (auto piecePressedSquare: piecesPressedSquare)
            window.draw(*piecePressedSquare);
    }
}

void Play::update(sf::RenderWindow &window, int &currentState) {
    if (!inCurrentState) currentState = 1;
}

Play::~Play() = default;
