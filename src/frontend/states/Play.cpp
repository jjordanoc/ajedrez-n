#include "Play.h"

Play::Play() = default;

void Play::handleEvents(sf::RenderWindow &window) {
    inCurrentState = true;
    sf::Event event{};

    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        inCurrentState = false;
                        break;
                }
        }
    }
}

void Play::render(sf::RenderWindow &window) {
    window.clear(sf::Color::Cyan);
    draw(window);
    window.display();
}

void Play::draw(sf::RenderWindow &window) {

}

void Play::update(sf::RenderWindow &window, int &currentState) {
    if (!inCurrentState) {
        currentState = 1;
    }
}

Play::~Play() = default;
