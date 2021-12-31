#include <windows.h>
#include <iostream>
#include <string>
#include <map>
#include "Game.h"
#include "GamePlayMode.h"
#include "GameLoadMode.h"

using std::map;

FlagsMode getMode(int argc, char* argv[]) {
	map<string, bool> flags = {
		{"-load", false},
		{"-save", false},
		{"-silent", false}
	};

	for (int i = 1; i < argc; i++) {
		try {
			flags.at(argv[i]) = true;
		}
		catch (const std::out_of_range& err) {
			std::cerr << "Invalid flag - Out of Range error: " << err.what() << '\n';
		}
	}

	if (flags["-save"])
		return FlagsMode::SAVE;
	else if (flags["-load"] && flags["-silent"])
		return FlagsMode::LOAD_SILENT;
	else if (flags["-load"])
		return FlagsMode::LOAD;
	else 
		return FlagsMode::REGULAR;
}

int main(int argc, char* argv[]) {
	FlagsMode flagMode = getMode(argc, argv);
	bool isStartPressed = false;

	Game* game;

	if (flagMode == FlagsMode::SAVE) {
		game = new GamePlayMode;
		((GamePlayMode*)game)->setIsSaveMode(true);

		while (true) {
			do {
				isStartPressed = game->menu();
			} while (!isStartPressed);
			game->play();
		}
	}
	

	return 0;
}