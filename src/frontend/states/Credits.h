#ifndef PROYECTOPROGRA2_CREDITS_H
#define PROYECTOPROGRA2_CREDITS_H


#pragma once

#include <iostream>

#include "../states/State.h"
#include "../graphics/Label.h"
#include "../global/Paths.h"

#include <SFML/Graphics.hpp>



#define members 5

using namespace std;

class Credits: public State {
private:
    sf::Font font;
    Label* title;
    Label* creditosLabel;
    Label* membersLabel[members]{};

    // Declarar el fondo
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
public:
    Credits();

    void handleEvents(sf::RenderWindow& window) override;

    void render(sf::RenderWindow& window) override;

    void draw(sf::RenderWindow& window) override;

    void update(sf::RenderWindow& window, int& currentState) override;

    ~Credits();
};


#endif //PROYECTOPROGRA2_CREDITS_H
