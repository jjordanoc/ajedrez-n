#ifndef PROYECTOPROGRA2_MAINMENU_H
#define PROYECTOPROGRA2_MAINMENU_H
#pragma once

#include <iostream>

#include "../graphics/Label.h"
#include "State.h"

#include <SFML/Graphics.hpp>

#include "../global/Paths.h"

#define Max_main_menu 4

using namespace std;

class MainMenu : public State {
private:
    int optionMenu;
    sf::Font font;
    Label *mainMenuTitle;
    Label *mainMenuLabel[Max_main_menu]{};

    // Declarar el fondo
    sf::Texture backgroundTexture;
    sf::RectangleShape background;

    bool inMenu = true;

public:
    MainMenu();

    void draw(sf::RenderWindow &window) override;

    void handleEvents(sf::RenderWindow &window) override;

    void render(sf::RenderWindow &window) override;

    void update(sf::RenderWindow &window, int &currentState) override;

    void moveUp();
    void moveDown();

    int mainMenuPressed() {
        return optionMenu;
    }

    ~MainMenu();
};


#endif//PROYECTOPROGRA2_MAINMENU_H
