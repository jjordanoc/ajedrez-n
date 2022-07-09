#ifndef PROYECTO_RULES_H
#define PROYECTO_RULES_H

#pragma once

#include <iostream>
#include <string>

#include "../graphics/Label.h"
#include "State.h"

#include <SFML/Graphics.hpp>

#include "global/Paths.h"
#include "global/Window.h"

class Rules: public State {
private:
    // Declarar el fondo
    sf::Texture backgroundTexture;
    sf::RectangleShape background;

    sf::Font font;
    std::unique_ptr<Label> titleLabel;
    std::unique_ptr<Label> titleN;
    std::unique_ptr<Label> rulesLabel;
    std::unique_ptr<Label> backLabel;

    // Rules
    std::unique_ptr<Label> rule1;
    std::unique_ptr<Label> rule2;
    std::unique_ptr<Label> rule3;
    std::unique_ptr<Label> rule4;
public:
    Rules();

    void handleEvents(sf::RenderWindow& window) override;

    void render(sf::RenderWindow& window) override;

    void draw(sf::RenderWindow& window) override;

    void update(sf::RenderWindow& window, int& currentState) override;

    ~Rules() override;
};


#endif//PROYECTO_RULES_H
