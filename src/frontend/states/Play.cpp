#include "Play.h"
#include <thread>

Play::Play() {
    boardTexture.loadFromFile("../../src/frontend/assets/textures/board.png");
    boardSprite.setTexture(&boardTexture);
    drawBoard();
}

void Play::drawBoard() {
    boardSprite.setSize(sf::Vector2f(600, 600));
    float boardX = windowWidth / 2.0 - 600 / 2.0;
    float boardY = windowHeight / 2.0 - 600 / 2.0;
    boardSprite.setPosition(boardX, boardY);
}

void Play::piecePressed(sf::RenderWindow &window, double windowX, double windowY) {
    int col, row;
    if (boardX <= windowX && windowX <= boardX + 600 && boardY <= windowY && windowY <= boardY + 600) {
        col = (windowX - boardX) / 75.0;
        row = (windowY - boardY) / 75.0;

        auto currentBoard = engine.getBoard().getBoardData();
        auto currentPiece = currentBoard.at(row).at(col);

        int counter = 0;
        if (currentPiece != nullptr && currentPiece->getColor() == chess::WHITE) {
            piecesPressedSquare.clear();
            possibleMoves.clear();
            posPieceSelected = make_pair(row, col);

            if (piecesPressedSquare.empty()) {
                for (auto c: currentPiece->possibleMoves(row, col, engine.getBoard())) {
                    possibleMoves.emplace_back(make_pair(c.second * 75.0 + boardX, c.first * 75.0 + boardY));
                }
            } else {
                for (auto c: currentPiece->possibleMoves(row, col, engine.getBoard())) {
                    *(std::next(std::begin(possibleMoves), counter++)) = make_pair(c.second * 75.0 + boardX, c.first * 75.0 + boardY);
                }
            }
        }

        counter = 0;
        if (piecesPressedSquare.empty()) {
            for (auto possibleMove: possibleMoves) {
                auto piecePressedSquare = new sf::RectangleShape{sf::Vector2f(75.f, 75.f)};
                piecePressedSquare->setFillColor(sf::Color(0, 191, 104, 200));
                piecePressedSquare->setPosition(possibleMove.first, possibleMove.second);
                piecesPressedSquare.emplace_back(piecePressedSquare);
            }
        } else {
            for (auto possibleMove: possibleMoves) {
                auto piecePressedSquare = new sf::RectangleShape{sf::Vector2f(75.f, 75.f)};
                piecePressedSquare->setFillColor(sf::Color(0, 191, 104, 200));
                piecePressedSquare->setPosition(possibleMove.first, possibleMove.second);
                *(std::next(std::begin(piecesPressedSquare), counter++)) = piecePressedSquare;
            }
        }
    }
}

void Play::piecePossibleMoveSquarePressed(sf::RenderWindow &window, double windowX, double windowY) {
    if (boardX <= windowX && windowX <= boardX + 600 && boardY <= windowY && windowY <= boardY + 600) {
        for (auto possibleMove: possibleMoves) {
            if ((possibleMove.first <= windowX && windowX <= possibleMove.first + 75.0) && (possibleMove.second <= windowY && windowY <= possibleMove.second + 75.0)) {
                auto &board = engine.getBoard();
                int newCol = (possibleMove.first - boardX) / 75.0;
                int newRow = (possibleMove.second - boardY) / 75.0;
                board.move(posPieceSelected.first, posPieceSelected.second, newRow, newCol);
                checkState();
                engine.nextTurn();
                piecesPressedSquare.clear();
                possibleMoves.clear();
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
                engine.forceGameOver();
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
                if (engine.getTurn() == chess::WHITE) {
                    piecePressed(window, event.mouseButton.x, event.mouseButton.y);
                    piecePossibleMoveSquarePressed(window, event.mouseButton.x, event.mouseButton.y);
                }
                break;
        }
    }
}

void Play::render(sf::RenderWindow &window) {
    // main game loop
    if (!isEndGame) {
        window.clear(sf::Color::Black);
        draw(window);
        window.display();
    } else {
        window.clear(sf::Color::Black);
        draw(window);
        string information;
        if (isDraw) {
            information = "It's a draw.";
        } else {
            string winnerString;
            if (engine.getWinner() == chess::GameState::WHITE_WINS) {
                winnerString = "White";
            }
            else if (engine.getWinner() == chess::GameState::BLACK_WINS) {
                winnerString = "Black";
            }
            information = winnerString + " wins.";
        }
        auto label = Label(FONT_PATH, sf::Color::Black, information, 100, (windowWidth / 2) - 50, (windowHeight / 2) + 50);
        label.draw(window);
        window.display();
    }
}

void Play::draw(sf::RenderWindow &window) {
    auto currentBoard = engine.getBoard().getBoardData();
    window.draw(boardSprite);
    if (std::size(piecesPressedSquare) != 0) {
        for (auto piecePressedSquare: piecesPressedSquare)
            window.draw(*piecePressedSquare);
    }
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            auto piece = currentBoard.at(i).at(j);
            if (piece != nullptr) {
                if (engine.getTurn() == chess::WHITE && dynamic_pointer_cast<chess::King>(piece) != nullptr && dynamic_pointer_cast<chess::King>(piece)->getIsInCheck()) {
                    auto piecePressedSquare = new sf::RectangleShape{sf::Vector2f(75.f, 75.f)};
                    piecePressedSquare->setFillColor(sf::Color(190, 0, 0, 200));
                    piecePressedSquare->setPosition(j * 75.0 + boardX, i * 75.0 + boardY);
                    window.draw(*piecePressedSquare);
                }
                piece->drawPiece(window, i, j);
            }
        }
    }
}

void Play::update(sf::RenderWindow &window, int &currentState) {
    if (!inCurrentState) currentState = 1;
}

void Play::checkState() {
    auto currentBoard = engine.getBoard();
    // Check states
    if (currentBoard.isCheckMate(chess::WHITE)) {
        isEndGame = true;
        winner = chess::WHITE;
    } else if (currentBoard.isCheckMate(chess::BLACK)) {
        winner = chess::BLACK;
        isEndGame = true;
    }

    if (engine.getBoard().isStaleMate(chess::WHITE) || engine.getBoard().isStaleMate(chess::BLACK) || engine.getBoard().fiftyMoveDraw()) {
        isEndGame = true;
        isDraw = true;
    }
}

Play::~Play() = default;
