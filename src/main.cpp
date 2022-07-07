#include "frontend/Game.h"
#include "../src/backend/game/AI.h"
#include "../src/backend/game/Engine.h"



int main() {
    auto game = Game::getInstance();
    game->run();

    return 0;
}

