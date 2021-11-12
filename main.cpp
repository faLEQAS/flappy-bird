#include <stdio.h>
#include <stdlib.h>
#include "game.hpp"

int main(int argc, char* argv[])
{
    while (true)
    {
        Game* game = new Game(480, 640, "Flappy bird", "asset_file.txt");
        game->loop();
        delete game;
    }
	return 0;
}