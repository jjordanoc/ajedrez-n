#ifndef PROYECTO_PLAY_H
#define PROYECTO_PLAY_H
#pragma once

#include <iostream>

#include "../global/Window.h"

#include "../graphics/Label.h"
#include "State.h"

#include <SFML/Graphics.hpp>

#include "../global/Paths.h"

using namespace std;


class Play: public State {
private:
    int sz = 60;
    int board[8][8] = {
            -5, -4, -3, -2, -1, -3, -4, -5,
            -6, -6, -6, -6, -6, -6, -6, -6,
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,
            0,  0,  0,  0,  0,  0,  0,  0,
            6,  6,  6,  6,  6,  6,  6,  6,
            5,  4,  3,  2,  1,  3,  4,  5
    };

    sf::Texture piecesTexture, boardTexture;
    sf::RectangleShape boardSprite;
    sf::Sprite f[32];

    void cargarPosicion();
public:
    Play();

    void draw(sf::RenderWindow &window) override;

    void handleEvents(sf::RenderWindow &window) override;

    void render(sf::RenderWindow &window) override;

    void update(sf::RenderWindow &window, int &currentState) override;

    ~Play();
};


#endif//PROYECTO_PLAY_H
