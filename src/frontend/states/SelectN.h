#ifndef PROYECTO_SELECTN_H
#define PROYECTO_SELECTN_H

#pragma once

#include <iostream>

#include "../graphics/Label.h"
#include "State.h"

#include <SFML/Graphics.hpp>

#include "../global/Paths.h"

using namespace std;

class SelectN : public State {
private:
    // Declarar el fondo
    sf::Texture backgroundTexture;
    sf::RectangleShape background;

    sf::Font font;
    unique_ptr<Label> titleLabel;
    unique_ptr<Label> titleNlabel;
    unique_ptr<Label> backLabel;
    unique_ptr<Label> playLabel;

    int optionSelectN;
public:
    SelectN();

    void handleEvents(sf::RenderWindow &window) override;

    void render(sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

    void update(sf::RenderWindow &window, int &currentState) override;

    ~SelectN();
};


#endif//PROYECTO_SELECTN_H
