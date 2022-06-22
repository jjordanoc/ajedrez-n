#include "SelectN.h"
SelectN::SelectN() {
    // Cargar el fondo
    backgroundTexture.loadFromFile(BACKGROUND_PATH);
    background.setSize(sf::Vector2f(960, 720));
    background.setTexture(&backgroundTexture);

    // Titulo
    titleLabel = make_unique<Label>(FONT_PATH, sf::Color::White, "AJEDREZ", 100, 245, 50);
    // ^n
    titleNlabel = make_unique<Label>(FONT_PATH, sf::Color::White, "n", 50, 715, 50);
    // Back button
    backLabel = make_unique<Label>(FONT_PATH, sf::Color::White, "Back", 50, 10, 640);
    // Play button
    playLabel = make_unique<Label>(FONT_PATH, sf::Color::White, "Play", 50, 837, 640);
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
                }
                else {
                    backLabel->setFillColor(sf::Color::White);
                }
                // Play button
                if ((event.mouseMove.x >= 837 && event.mouseMove.x <= 943) && (event.mouseMove.y >= 640 && event.mouseMove.y <= 690)) {
                    playLabel->setFillColor(sf::Color::Black);
                }
                else {
                    playLabel->setFillColor(sf::Color::White);
                }
                break;
            case sf::Event::MouseButtonPressed:
                // If left mouse button is pressed
                if (event.mouseButton.button == 0) {
                    // Back button
                    if ((event.mouseButton.x >= 10 && event.mouseButton.x <= 160) && (event.mouseButton.y >= 640 && event.mouseButton.y <= 690)) {
                        optionSelectN = 0;
                        inCurrentState = false;
                    }
                    // Play button
                    if ((event.mouseButton.x >= 837 && event.mouseButton.x <= 943) && (event.mouseButton.y >= 640 && event.mouseButton.y <= 690)) {
                        optionSelectN = 1;
                        inCurrentState = false;
                    }
                }
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
}

void SelectN::update(sf::RenderWindow &window, int &currentState) {
    if (!inCurrentState) {
        if (optionSelectN == 0) currentState = 0;
        if (optionSelectN == 1) currentState = 4;
    }
}

SelectN::~SelectN() = default;
