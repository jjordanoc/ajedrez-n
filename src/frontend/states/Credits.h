#ifndef PROYECTOPROGRA2_CREDITS_H
#define PROYECTOPROGRA2_CREDITS_H


#pragma once

#include <iostream>
#include <memory>

#include "../states/State.h"
#include "../graphics/Label.h"

#include "global/Paths.h"
#include "global/Window.h"

#include <SFML/Graphics.hpp>


#define members 5

using namespace std;

class Credits: public State {
private:
    // Declarar el fondo
    sf::Texture backgroundTexture;
    sf::RectangleShape background;

    sf::Font font;
    unique_ptr<Label> titleLabel;
    unique_ptr<Label> titleN;
    unique_ptr<Label> creditosLabel;
    Label* membersLabel[members]{};
    unique_ptr<Label> backLabel;
public:
    Credits();

    void handleEvents(sf::RenderWindow& window) override;

    void render(sf::RenderWindow& window) override;

    void draw(sf::RenderWindow& window) override;

    void update(sf::RenderWindow& window, int& currentState) override;

    ~Credits() override;
};


#endif //PROYECTOPROGRA2_CREDITS_H
