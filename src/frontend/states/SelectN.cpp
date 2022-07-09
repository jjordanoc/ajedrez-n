#include "SelectN.h"
#include "backend/game/Engine.h"
#include "global/Global.h"

SelectN::SelectN() {
    // Cargar el fondo
    backgroundTexture.loadFromFile(BACKGROUND_PATH);
    background.setSize(sf::Vector2f(windowWidth, windowHeight));
    background.setTexture(&backgroundTexture);

    // Titulo
    titleLabel = std::make_unique<Label>(FONT_PATH, sf::Color::White, "AJEDREZ", 100, 245, 50);
    // ^n
    titleNlabel = std::make_unique<Label>(FONT_PATH, sf::Color::White, "n", 50, 715, 50);
    // Back button
    backLabel = std::make_unique<Label>(FONT_PATH, sf::Color::White, "Back", 50, 10, 640);
    // Play button
    playLabel = std::make_unique<Label>(FONT_PATH, sf::Color::White, "Play", 50, 837, 640);

    // Input N
    inputNlabel = std::make_unique<Label>(FONT_PATH, sf::Color::White, nValue, 60, 480 - 30, 360);
    // N dialog
    dialogN = std::make_unique<Label>(FONT_PATH, sf::Color::White, "N: ", 60, 480 - 30 - 60 - 20, 360);
}

void SelectN::handleEvents(sf::RenderWindow &window) {
    inCurrentState = true;
    sf::Event event{};

    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                // Back button
                if ((event.mouseMove.x >= 10 && event.mouseMove.x <= 160) && (event.mouseMove.y >= 640 && event.mouseMove.y <= 690)) {
                    backLabel->setFillColor(sf::Color::Black);
                } else {
                    backLabel->setFillColor(sf::Color::White);
                }
                // Play button
                if ((event.mouseMove.x >= 837 && event.mouseMove.x <= 943) && (event.mouseMove.y >= 640 && event.mouseMove.y <= 690)) {
                    playLabel->setFillColor(sf::Color::Black);
                } else {
                    playLabel->setFillColor(sf::Color::White);
                }
                break;
            case sf::Event::MouseButtonPressed:
                // If left mouse button is pressed
                if (event.mouseButton.button == 0) {
                    // Back button
                    if ((event.mouseButton.x >= 10 && event.mouseButton.x <= 160) && (event.mouseButton.y >= 640 && event.mouseButton.y <= 690)) {
                        option = 0;
                        inCurrentState = false;
                    }
                    // Play button
                    if (!nValue.empty()) {
                        if ((event.mouseButton.x >= 837 && event.mouseButton.x <= 943) && (event.mouseButton.y >= 640 && event.mouseButton.y <= 690)) {
                            option = 1;
                            inCurrentState = false;
                            chess::Engine::getInstance().initBoard(stoi(nValue));
                        }
                    }
                }
                break;
            case sf::Event::TextEntered:
                // Unicode = 8 is the unicode of backslash
                if (event.text.unicode == 8 && !nValue.empty()) {
                    nValue.pop_back();
                } else if (48 <= event.text.unicode && event.text.unicode <= 57) {
                    nValue.push_back((char) event.text.unicode);
                }
                inputNlabel->setNewText(nValue);
                break;
        }
    }
}

void SelectN::render(sf::RenderWindow &window) {
    window.clear();
    window.draw(background);
    draw(window);
    window.display();
}

void SelectN::draw(sf::RenderWindow &window) {
    titleLabel->draw(window);
    titleNlabel->draw(window);
    backLabel->draw(window);
    playLabel->draw(window);

    dialogN->draw(window);
    inputNlabel->draw(window);
}

void SelectN::update(sf::RenderWindow &window, int &currentState) {
    if (!inCurrentState) {
        if (option == 0) currentState = 0;
        if (option == 1) currentState = 4;
    }
}

SelectN::~SelectN() = default;
