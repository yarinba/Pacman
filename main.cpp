#include <windows.h>
#include <iostream>

#include "Game.h"

int main() {
	bool isStartPressed = false;
	Game game;

	game.init();
	do {
		isStartPressed = game.menu();
	} while (!isStartPressed);
	game.run();
}