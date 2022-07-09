#include "MainMenu.h"

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
    mainMenuLabel[1] = new Label(FONT_PATH, sf::Color::White, "Opciones", 70, 400, 300);
    //Opcion créditos
    mainMenuLabel[2] = new Label(FONT_PATH, sf::Color::White, "Creditos", 70, 400, 400);
    //Opcion salir
    mainMenuLabel[3] = new Label(FONT_PATH, sf::Color::White, "Salir", 70, 400, 500);

    mainMenuLabel[0]->setFillColor(sf::Color::Black);  // comienza en negro ya que es la opcion por defecto
    optionMenu = 0;
}

void MainMenu::handleEvents(sf::RenderWindow &window) {
    inCurrentState = true;
    sf::Event event{};

    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
            case sf::Event::KeyReleased:
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        moveUp();
                        break;
                    case sf::Keyboard::Down:
                        moveDown();
                        break;
                    case sf::Keyboard::Return:
                        inCurrentState = false;
                        break;
                }
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
    for (auto& label : mainMenuLabel){
        label->draw(window);
    }
}

void MainMenu::update(sf::RenderWindow &window, int& currentState) {
    if (!inCurrentState) {
        if (mainMenuPressed() == 3)
            window.close();
        else {
            currentState = mainMenuPressed() + 1;
        }
    }
}

void MainMenu::moveUp() {
    if (optionMenu - 1 >= 0) {
        mainMenuLabel[optionMenu]->setFillColor(sf::Color::White);

        optionMenu--;
        if (optionMenu == -1) {
            optionMenu = 4;
        }
        mainMenuLabel[optionMenu]->setFillColor(sf::Color::Black);
    }
}

void MainMenu::moveDown() {
    if (optionMenu + 1 <= Max_main_menu) {
        mainMenuLabel[optionMenu]->setFillColor(sf::Color::White);

        optionMenu++;
        if (optionMenu == 4) {
            optionMenu = 0;
        }
        mainMenuLabel[optionMenu]->setFillColor(sf::Color::Black);
    }
}

MainMenu::~MainMenu() {
    for (auto& label : mainMenuLabel){
        delete label;
    }
}


