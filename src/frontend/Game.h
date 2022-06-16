#ifndef PROYECTOPROGRA2_GAME_H
#define PROYECTOPROGRA2_GAME_H

#include <cmath>
#include <iostream>

#include "states/Credits.h"
#include "states/MainMenu.h"
#include "states/State.h"

#include <SFML/Graphics.hpp>

#define numberOfStates 4


class Game {
private:
    inline static Game *instance = nullptr;
    Game();

    // Instanciamos la pantalla principal del juego
    sf::RenderWindow gameWindow{sf::VideoMode(960, 720), "Main Menu", sf::Style::Default};

    // States
    State *states[numberOfStates]{};
    int currentState;

public:
    inline static Game *getInstance() {
        if (instance == nullptr) {
            instance = new Game();
        }
        return instance;
    }

    void run();

    virtual ~Game();
};

#endif//PROYECTOPROGRA2_GAME_H
