#ifndef PROYECTO_PLAY_H
#define PROYECTO_PLAY_H
#pragma once

#include <iostream>

#include "../graphics/Label.h"
#include "State.h"

#include <SFML/Graphics.hpp>

#include "../global/Paths.h"

using namespace std;


class Play: public State {
private:
public:
    Play();

    void draw(sf::RenderWindow &window) override;

    void handleEvents(sf::RenderWindow &window) override;

    void render(sf::RenderWindow &window) override;

    void update(sf::RenderWindow &window, int &currentState) override;

    ~Play();
};


#endif//PROYECTO_PLAY_H
