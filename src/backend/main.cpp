
#include "game/Engine.h"
#include <iostream>

int main() {
    chess::Engine *engine = chess::Engine::get_instance();
    engine->initBoard();
    engine->initGame();

    return 0;
}
