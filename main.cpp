#include <windows.h>
#include <iostream>
#include <fstream>
#include "Game.h"
#include <string>
#include "Map.h"

int main(int argc,char* argv[]) {
	bool isStartPressed = false;
	Game game;

	while (true) {
		game.init();
		do {
			isStartPressed = game.menu();
		} while (!isStartPressed);
		game.run();
	

}