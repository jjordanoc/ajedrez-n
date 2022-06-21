#include "Game.h"

Game::Game() {
    // States
    states[0] = (State *)(new MainMenu());  // MainMenu
    states[1] = (State *)new Credits();  // Play
    states[2] = (State *)new Credits();  // Options
    states[3] = (State *)(new Credits());  // Credits

    currentState = 0;  // empezamos en el menu principal
}

void Game::run() {
    // Game loop
    while (gameWindow.isOpen()) {
        states[currentState]->handleEvents(gameWindow);
        states[currentState]->render(gameWindow);
        states[currentState]->update(gameWindow, currentState);
    }
}

Game::~Game() {
    delete instance;
}
