#include <windows.h>
#include <iostream>
#include <string>
#include "Game.h"


int main() {
	bool isStartPressed = false;
	Game game;
	
	// TODO: everytime game is finished - delete allocations of ghosts
	while (true) {
		do {
			isStartPressed = game.menu();
		} while (!isStartPressed);
		game.playChosenMode();
	}

	return 0;
}