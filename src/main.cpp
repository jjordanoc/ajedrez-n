#include "frontend/Game.h"


int main() {
    auto game = Game::getInstance();
    game->run();
}