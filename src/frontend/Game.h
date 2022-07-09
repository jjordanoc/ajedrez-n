#ifndef PROYECTOPROGRA2_GAME_H
#define PROYECTOPROGRA2_GAME_H

#include <iostream>
#include <cmath>
#include <memory>

#include "global/Window.h"

#include "states/Credits.h"
#include "states/MainMenu.h"
#include "states/State.h"

#include "states/SelectN.h"
#include "states/Play.h"
#include <thread>

#include <SFML/Graphics.hpp>

#define numberOfStates 5


class Game {
private:
    // Instanciamos la pantalla principal del juego
    sf::RenderWindow gameWindow{sf::VideoMode(windowWidth, windowHeight), "Ajedrez"};
    chess::AI ai = chess::AI(chess::BLACK, 3);
    chess::Engine &engine = chess::Engine::getInstance();
    sf::Image windowIcon;
    // States
    State *states[numberOfStates]{};
    int currentState;
    void AIMove();
    Game();
public:
    static Game &getInstance();
    void run();
    ~Game();
};

#endif//PROYECTOPROGRA2_GAME_H
