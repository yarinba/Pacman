#include <windows.h>
#include <iostream>

#include "Game.h"

int main() {
	bool isStartPressed = false;
	Game game;

	// TODO: everytime game is finished - delete allocations of ghosts
	while (true) {
		game.init();
		do {
			isStartPressed = game.menu();
		} while (!isStartPressed);
		game.run();
	}
}