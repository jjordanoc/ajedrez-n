#include "Credits.h"

Credits::Credits() {
    string font_path = "../src/frontend/assets/fonts/Montserrat-Thin.ttf";

    // Titulo
    title = new Label(font_path, sf::Color::White, "AJEDREZ^n", 100, 200, 50);

    // Credits
    creditosLabel = new Label(font_path, sf::Color::White, "Credits:", 80, 200, 200);
    // Integrantes
    membersLabel[0] = new Label(font_path, sf::Color::White, "Josue Arriaga", 70, 200, 300);
    membersLabel[1] = new Label(font_path, sf::Color::White, "Jose Chachi", 70, 200, 400);
    membersLabel[2] = new Label(font_path, sf::Color::White, "Joaquin O'connor", 70, 200, 500);
    membersLabel[3] = new Label(font_path, sf::Color::White, "Nicolas Arroyo", 70, 200, 600);
    membersLabel[4] = new Label(font_path, sf::Color::White, "Nicolas Arroyo", 70, 200, 700);

    // Cargar el fondo
    backgroundTexture.loadFromFile("../src/frontend/assets/textures/backgroundMenu2.jpg");
    background.setSize(sf::Vector2f(960, 720));
    background.setTexture(&backgroundTexture);
}

void Credits::handleEvents(sf::RenderWindow &window) {
    sf::Event event{};

    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
            case sf::Event::KeyReleased:
                cout << "Tecla presionada\n";
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
    title->draw(window);
    creditosLabel->draw(window);
    for (auto& label : membersLabel){
        label->draw(window);
    }
}

void Credits::update(sf::RenderWindow &window, int& currentState) {

}

Credits::~Credits() {
    delete title;
    delete creditosLabel;
    for (auto& label : membersLabel){
        delete label;
    }
}
