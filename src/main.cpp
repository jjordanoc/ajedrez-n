#include "../src/backend/game/AI.h"
#include "../src/backend/game/Engine.h"
#include "frontend/Game.h"


int main() {
    Game &game = Game::getInstance();
    game.run();
    return 0;
}
