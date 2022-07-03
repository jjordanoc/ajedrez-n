#ifndef PROYECTO_PLAY_H
#define PROYECTO_PLAY_H
#pragma once


#include <iostream>
#include <memory>

#include "State.h"
#include "../graphics/Label.h"

#include <SFML/Graphics.hpp>

#include "../global/Window.h"
#include "../global/Paths.h"

#include "../../backend/global/Global.h"
#include "../../backend/game/Engine.h"
#include "../../backend/game/AI.h"
#include "../../backend/pieces/Piece.h"


using namespace std;


class Play: public State {
private:
    sf::Texture boardTexture;
    sf::RectangleShape boardSprite;

    std::vector<std::pair<float, float>> possibleMoves;
    std::vector<sf::RectangleShape*> piecesPressedSquare;

    pair<chess::PosType, chess::PosType> posPieceSelected;

    chess::Engine &engine = chess::Engine::getInstance();

    bool isEndGame = false;
    chess::Color winner;

    chess::AI ai = chess::AI(chess::BLACK, 5);

    void drawBoard();
    void piecePressed(sf::RenderWindow &window, double windowX, double windowY);
    void piecePossibleMoveSquarePressed(sf::RenderWindow &window, double windowX, double windowY);
public:
    Play();

    void draw(sf::RenderWindow &window) override;

    void handleEvents(sf::RenderWindow &window) override;

    void render(sf::RenderWindow &window) override;

    void update(sf::RenderWindow &window, int &currentState) override;

    void checkState();

    ~Play();
};


#endif//PROYECTO_PLAY_H
