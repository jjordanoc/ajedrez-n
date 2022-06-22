#ifndef PROYECTOPROGRA2_GAME_H
#define PROYECTOPROGRA2_GAME_H

#include <iostream>
#include <cmath>
#include <memory>

#include "states/Credits.h"
#include "states/MainMenu.h"
#include "states/State.h"

#include "states/SelectN.h"
#include "states/Play.h"

#include <SFML/Graphics.hpp>

#define numberOfStates 5


class Game {
private:
    // Instanciamos la pantalla principal del juego
    sf::RenderWindow gameWindow{sf::VideoMode(960, 720), "Ajedrez", sf::Style::Default};

    // States
    State *states[numberOfStates]{};
    int currentState;

    inline static Game *instance = nullptr;
    Game();
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
