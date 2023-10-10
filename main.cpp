#include <SFML/Graphics.hpp>
#include "game.h"


int main()
{
	Game* game;
	game = new Game();
	game->play();
}