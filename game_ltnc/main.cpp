#include "Game.h"
int main(int argc, char* argv[])
{
    Game game;
    game.initThreatsList();
    if (!game.init()) {
        return -1;
    }

    GameState gameState = MENU;

    while (gameState != EXIT) {
        if (gameState == MENU) {
            gameState = game.showMenu();
        }
        else if (gameState == PLAY) {
            gameState = game.run();
        }
    }

    game.cleanup();
    return 0;
}
