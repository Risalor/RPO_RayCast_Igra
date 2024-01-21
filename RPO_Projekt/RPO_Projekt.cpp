#include "Game.h"
#include <windows.h>

int main() {


    ShowWindow(GetConsoleWindow(), 0);
    Game game;

    game.run();
}