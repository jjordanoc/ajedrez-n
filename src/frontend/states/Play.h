#ifndef PROYECTO_PLAY_H
#define PROYECTO_PLAY_H
#pragma once


#include <iostream>


#include "../graphics/Label.h"
#include "State.h"

#include <SFML/Graphics.hpp>

#include "../global/Window.h"
#include "../global/Paths.h"

#include "../../backend/game/Engine.h"

using namespace std;


class Play: public State {
private:
    sf::Texture boardTexture;
    sf::RectangleShape boardSprite;

    chess::Engine &engine = chess::Engine::getInstance();

    void drawBoard();
    void piecePressed(double x, double y);
public:
    Play();

    void draw(sf::RenderWindow &window) override;

    void handleEvents(sf::RenderWindow &window) override;

    void render(sf::RenderWindow &window) override;

    void update(sf::RenderWindow &window, int &currentState) override;

    ~Play();
};


#endif//PROYECTO_PLAY_H
