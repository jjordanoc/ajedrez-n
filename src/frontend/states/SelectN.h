#ifndef PROYECTO_SELECTN_H
#define PROYECTO_SELECTN_H

#pragma once

#include <iostream>
#include <string>

#include "../graphics/Label.h"
#include "State.h"

#include <SFML/Graphics.hpp>

#include "global/Paths.h"
#include "global/Window.h"


class SelectN : public State {
private:
    // Declarar el fondo
    sf::Texture backgroundTexture;
    sf::RectangleShape background;

    sf::Font font;
    std::unique_ptr<Label> titleLabel;
    std::unique_ptr<Label> titleNlabel;
    std::unique_ptr<Label> backLabel;
    std::unique_ptr<Label> playLabel;

    // Input N
    std::string nValue;
    std::unique_ptr<Label> dialogN;
    std::unique_ptr<Label> inputNlabel;

    int option;// 0: back y 1: play
public:
    SelectN();

    void handleEvents(sf::RenderWindow &window) override;

    void render(sf::RenderWindow &window) override;

    void draw(sf::RenderWindow &window) override;

    void update(sf::RenderWindow &window, int &currentState) override;

    ~SelectN();
};


#endif//PROYECTO_SELECTN_H
