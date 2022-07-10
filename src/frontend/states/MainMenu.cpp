#include "MainMenu.h"
#include "backend/game/Engine.h"

MainMenu::MainMenu() {
    // Cargar el fondo
    backgroundTexture.loadFromFile(BACKGROUND_PATH);
    background.setSize(sf::Vector2f(windowWidth, windowHeight));
    background.setTexture(&backgroundTexture);

    // Titulo
    mainMenuTitle = std::make_unique<Label>(FONT_PATH, sf::Color::White, "AJEDREZ", 100, 245, 50);
    // ^n
    mainMenuTitleN = std::make_unique<Label>(FONT_PATH, sf::Color::White, "n", 50, 715, 50);
    //Opcion play
    mainMenuLabel[0] = new Label(FONT_PATH, sf::Color::White, "Jugar", 70, 400, 200);
    //Opcion opciones
    mainMenuLabel[1] = new Label(FONT_PATH, sf::Color::White, "Reglas", 70, 400, 300);
    //Opcion créditos
    mainMenuLabel[2] = new Label(FONT_PATH, sf::Color::White, "Creditos", 70, 400, 400);
    //Opcion salir
    mainMenuLabel[3] = new Label(FONT_PATH, sf::Color::White, "Salir", 70, 400, 500);
}

void MainMenu::handleEvents(sf::RenderWindow &window) {
    inCurrentState = true;
    sf::Event event{};

    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
            case sf::Event::MouseMoved:
                // Button play
                if ((event.mouseMove.x >= 400 && event.mouseMove.x <= 590) && (event.mouseMove.y >= 200 && event.mouseMove.y <= 270)) {
                    mainMenuLabel[0]->setFillColor(sf::Color::Black);
                } else {
                    mainMenuLabel[0]->setFillColor(sf::Color::White);
                }
                // Button rules
                if ((event.mouseMove.x >= 400 && event.mouseMove.x <= 630) && (event.mouseMove.y >= 300 && event.mouseMove.y <= 370)) {
                    mainMenuLabel[1]->setFillColor(sf::Color::Black);
                } else {
                    mainMenuLabel[1]->setFillColor(sf::Color::White);
                }
                // Button credits
                if ((event.mouseMove.x >= 400 && event.mouseMove.x <= 680) && (event.mouseMove.y >= 400 && event.mouseMove.y <= 470)) {
                    mainMenuLabel[2]->setFillColor(sf::Color::Black);
                } else {
                    mainMenuLabel[2]->setFillColor(sf::Color::White);
                }
                // Button exit
                if ((event.mouseMove.x >= 400 && event.mouseMove.x <= 545) && (event.mouseMove.y >= 500 && event.mouseMove.y <= 570)) {
                    mainMenuLabel[3]->setFillColor(sf::Color::Black);
                } else {
                    mainMenuLabel[3]->setFillColor(sf::Color::White);
                }
                break;
            case sf::Event::MouseButtonPressed:
                // If left mouse button is pressed
                if (event.mouseButton.button == 0) {
                    // Button play
                    if ((event.mouseButton.x >= 400 && event.mouseButton.x <= 590) && (event.mouseButton.y >= 200 && event.mouseButton.y <= 270)) {
                        optionMenu = 0;
                        inCurrentState = false;
                    }
                    // Button rules
                    else if ((event.mouseButton.x >= 400 && event.mouseButton.x <= 630) && (event.mouseButton.y >= 300 && event.mouseButton.y <= 370)) {
                        optionMenu = 1;
                        inCurrentState = false;
                    }
                    // Button credits
                    else if ((event.mouseButton.x >= 400 && event.mouseButton.x <= 680) && (event.mouseButton.y >= 400 && event.mouseButton.y <= 470)) {
                        optionMenu = 2;
                        inCurrentState = false;
                    }
                    // Button exit
                    else if ((event.mouseButton.x >= 400 && event.mouseButton.x <= 545) && (event.mouseButton.y >= 500 && event.mouseButton.y <= 570)) {
                        optionMenu = 3;
                        inCurrentState = false;
                    }
                }
                break;
        }
    }
}

void MainMenu::render(sf::RenderWindow &window) {
    window.clear();
    window.draw(background);
    draw(window);
    window.display();
}

void MainMenu::draw(sf::RenderWindow &window) {
    mainMenuTitle->draw(window);
    mainMenuTitleN->draw(window);
    for (auto &label: mainMenuLabel) {
        label->draw(window);
    }
}

void MainMenu::update(sf::RenderWindow &window, int &currentState) {
    if (!inCurrentState) {
        if (optionMenu == 3) {
            chess::Engine::getInstance().forceGameOver();
            window.close();
        }
        else {
            currentState = optionMenu + 1;
        }
    }
}

MainMenu::~MainMenu() {
    for (auto &label: mainMenuLabel) {
        delete label;
    }
}
