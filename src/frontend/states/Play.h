#ifndef PROYECTO_PLAY_H
#define PROYECTO_PLAY_H
#pragma once


#include <iostream>
#include <memory>

#include "../graphics/Label.h"
#include "State.h"
#include <thread>

#include <SFML/Graphics.hpp>

#include "global/Paths.h"
#include "global/Window.h"

#include "../../backend/game/AI.h"
#include "../../backend/game/Engine.h"
#include "../../backend/pieces/Piece.h"
#include "global/Global.h"


using namespace std;


class Play : public State {
private:
    sf::Texture boardTexture;
    sf::RectangleShape boardSprite;
    std::vector<std::pair<float, float>> possibleMoves;
    std::vector<sf::RectangleShape *> piecesPressedSquare;
    pair<chess::PosType, chess::PosType> posPieceSelected;
    chess::Engine &engine = chess::Engine::getInstance();
    bool isEndGame = false;
    bool isDraw = false;
    chess::Color winner;
    void drawBoard();
    void piecePressed(sf::RenderWindow &window, double windowX, double windowY);
    void piecePossibleMoveSquarePressed(sf::RenderWindow &window, double windowX, double windowY);

public:
    Play();

    void draw(sf::RenderWindow &window) override;

    void handleEvents(sf::RenderWindow &window);

    void render(sf::RenderWindow &window) override;

    void update(sf::RenderWindow &window, int &currentState) override;

    void checkState();

    ~Play();
};


#endif//PROYECTO_PLAY_H
