#include "Rules.h"

Rules::Rules() {
    // Cargar el fondo
    backgroundTexture.loadFromFile(BACKGROUND_PATH);
    background.setSize(sf::Vector2f(windowWidth, windowHeight));
    background.setTexture(&backgroundTexture);

    // Titulo
    titleLabel = std::make_unique<Label>(FONT_PATH, sf::Color::White, "AJEDREZ", 100, 250, 20);
    // ^n
    titleN = std::make_unique<Label>(FONT_PATH, sf::Color::White, "n", 50, 715, 20);
    // Rules
    rulesLabel = std::make_unique<Label>(FONT_PATH, sf::Color::White, "Reglas:", 70, 25, 150);
    // Back button
    backLabel = std::make_unique<Label>(FONT_PATH, sf::Color::White, "Volver", 50, 10, 640);

    // Rules
    rule1 = std::make_unique<Label>(FONT_PATH, sf::Color::White, "- Si n es 0, el juego es identico al ajedrez clasico.", 28, 40, 245);
    rule2 = std::make_unique<Label>(FONT_PATH, sf::Color::White, "- Si n es multiplo de 7, los caballos se mueven doble.", 28, 40, 315);
    rule3 = std::make_unique<Label>(FONT_PATH, sf::Color::White, "- Si n es multiplo de 9, ceil(log9(n)*|cos(n)|) peones se vuelven reinas.", 28, 40, 385);
    rule4 = std::make_unique<Label>(FONT_PATH, sf::Color::White, "- Las torres se mueven ceil(|8 - log67(n)|) casillas.", 28, 40, 455);
}

void Rules::handleEvents(sf::RenderWindow &window) {
    inCurrentState = true;
    sf::Event event{};

    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
                if ((event.mouseMove.x >= 10 && event.mouseMove.x <= 160) && (event.mouseMove.y >= 640 && event.mouseMove.y <= 690)) {
                    backLabel->setFillColor(sf::Color::Black);
                } else {
                    backLabel->setFillColor(sf::Color::White);
                }
                break;
            case sf::Event::MouseButtonPressed:
                // If left mouse button is pressed
                if (event.mouseButton.button == 0) {
                    if ((event.mouseButton.x >= 10 && event.mouseButton.x <= 160) && (event.mouseButton.y >= 640 && event.mouseButton.y <= 690)) {
                        inCurrentState = false;
                    }
                }
                break;
        }
    }
}

void Rules::render(sf::RenderWindow &window) {
    window.clear();
    window.draw(background);
    draw(window);
    window.display();
}

void Rules::draw(sf::RenderWindow &window) {
    titleLabel->draw(window);
    titleN->draw(window);
    rulesLabel->draw(window);
    backLabel->draw(window);
    rule1->draw(window);
    rule2->draw(window);
    rule3->draw(window);
    rule4->draw(window);
}

void Rules::update(sf::RenderWindow &window, int &currentState) {
    if (!inCurrentState) {
        currentState = 0;
    }
}

Rules::~Rules() = default;
