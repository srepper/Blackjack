#include "Game.h"

int main(int argc, char *args[])
{
	//Create and run a new Game
	Game *game = new Game();
	if(game->run() != 0)
	{
		return 1;
	}

    return 0;
}