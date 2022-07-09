#ifndef PROYECTOPROGRA2_STATE_H
#define PROYECTOPROGRA2_STATE_H

#include <SFML/Graphics.hpp>

class State {
protected:
    bool inCurrentState;

public:
    State() = default;

    virtual void handleEvents(sf::RenderWindow &window) = 0;

    virtual void render(sf::RenderWindow &window) = 0;

    virtual void draw(sf::RenderWindow &window) = 0;

    virtual void update(sf::RenderWindow &window, int &currentState) = 0;

    virtual ~State() = default;
};

#endif//PROYECTOPROGRA2_STATE_H
