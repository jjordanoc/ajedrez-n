#include "MainMenu.h"

MainMenu::MainMenu() {
    string font_path = "../src/frontend/assets/fonts/Montserrat-Thin.ttf";

    // Titulo
    mainMenuTitle = new Label(font_path, sf::Color::White, "AJEDREZ^n", 100, 200, 50);

    //Opcion play
    mainMenuLabel[0] = new Label(font_path, sf::Color::White, "Jugar", 70, 400, 200);
    //Opcion opciones
    mainMenuLabel[1] = new Label(font_path, sf::Color::White, "Opciones", 70, 400, 300);
    //Opcion créditos
    mainMenuLabel[2] = new Label(font_path, sf::Color::White, "Credits", 70, 400, 400);
    //Opcion salir
    mainMenuLabel[3] = new Label(font_path, sf::Color::White, "Salir", 70, 400, 500);

    mainMenuLabel[0]->setFillColor(sf::Color::Black);  // comienza en negro ya que es la opcion por defecto
    optionMenu = 0;

    // Cargar el fondo
    backgroundTexture.loadFromFile("../src/frontend/assets/textures/backgroundMenu2.jpg");
    background.setSize(sf::Vector2f(960, 720));
    background.setTexture(&backgroundTexture);
}

void MainMenu::draw(sf::RenderWindow &window) {
    mainMenuTitle->draw(window);
    for (auto& label : mainMenuLabel){
        label->draw(window);
    }
}

void MainMenu::handleEvents(sf::RenderWindow &window) {
    inMenu = true;
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
                        inMenu = false;
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

void MainMenu::update(sf::RenderWindow &window, int& currentState) {
    if (!inMenu) {
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
        cout << "Opcion del menu: " << optionMenu << endl;
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
        cout << "Opcion del menu: " <<  optionMenu << endl;
        mainMenuLabel[optionMenu]->setFillColor(sf::Color::Black);
    }
}

MainMenu::~MainMenu() {
    delete mainMenuTitle;
    for (auto& label : mainMenuLabel){
        delete label;
    }
}


