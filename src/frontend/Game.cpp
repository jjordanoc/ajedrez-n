#include "Game.h"

Game::Game() {
    // Set the window icon
    if (!windowIcon.loadFromFile("../../src/frontend/assets/textures/dark_pawn.png")) {
        cout << "No sale\n";
    }
    gameWindow.setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());
    // States
    states[0] = (State *)(new MainMenu());  // MainMenu
    states[1] = (State *)new SelectN();  // SelectN
    states[2] = (State *)new Credits();  // Options
    states[3] = (State *)(new Credits());  // Credits

    states[4] = (State *)(new Play());  // Play

    currentState = 0;  // empezamos en el menu principal
}

Game &Game::getInstance() {
    static Game instance;
    return instance;
}


void Game::run() {
    // Game loop

    // creamos thread de la ia para que corra separado del resto del juego
    thread AIThread;

    AIThread = thread([&](){
        AIMove();
    });

    // loop principal del juego, maneja input del jugador y dibujar el tablero
    while (gameWindow.isOpen()) {
        states[currentState]->handleEvents(gameWindow);
        states[currentState]->render(gameWindow);
        states[currentState]->update(gameWindow, currentState);
    }
    AIThread.join();
}

void Game::AIMove() {
    while(!engine.isGameOver()) {
        // si es turno de la AI
        if (engine.getTurn() == ai.getColor()) {
            // realizar movimiento
            ai.move(engine.getBoard());
            engine.checkState();
            engine.nextTurn();
        }
        // sino, dormir
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}
Game::~Game() {
    for (auto &st : states) {
        delete st;
    }
}
