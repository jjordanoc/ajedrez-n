#include "Credits.h"

Credits::Credits() {
    // Cargar el fondo
    backgroundTexture.loadFromFile(BACKGROUND_PATH);
    background.setSize(sf::Vector2f(windowWidth, windowHeight));
    background.setTexture(&backgroundTexture);

    // Titulo
    titleLabel = std::make_unique<Label>(FONT_PATH, sf::Color::White, "AJEDREZ", 100, 250, 20);
    // ^n
    titleN = std::make_unique<Label>(FONT_PATH, sf::Color::White, "n", 50, 715, 20);
    // Credits
    creditsLabel = std::make_unique<Label>(FONT_PATH, sf::Color::White, "Creditos:", 70, 60, 150);
    // Integrantes
    membersLabel[0] = new Label(FONT_PATH, sf::Color::White, "Josue Arriaga", 50, 100, 245);
    membersLabel[1] = new Label(FONT_PATH, sf::Color::White, "Jose Chachi", 50, 100, 315);
    membersLabel[2] = new Label(FONT_PATH, sf::Color::White, "Joaquin O'connor", 50, 100, 385);
    membersLabel[3] = new Label(FONT_PATH, sf::Color::White, "Renato Cernades", 50, 100, 455);
    membersLabel[4] = new Label(FONT_PATH, sf::Color::White, "Nicolas Arroyo", 50, 100, 525);
    // Back button
    backLabel = std::make_unique<Label>(FONT_PATH, sf::Color::White, "Back", 50, 10, 640);
}

void Credits::handleEvents(sf::RenderWindow &window) {
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
                }
                else {
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

void Credits::render(sf::RenderWindow &window) {
    window.clear();
    window.draw(background);
    draw(window);
    window.display();
}

void Credits::draw(sf::RenderWindow &window) {
    titleLabel->draw(window);
    titleN->draw(window);
    creditsLabel->draw(window);
    for (auto& label : membersLabel){
        label->draw(window);
    }
    backLabel->draw(window);
}

void Credits::update(sf::RenderWindow &window, int& currentState) {
    if (!inCurrentState) {
        currentState = 0;
    }
}

Credits::~Credits() {
    for (auto& label : membersLabel){
        delete label;
    }
}
