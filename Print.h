#pragma once

#include "utils.h"
#include "Game.h"


class Game;

class Print {
public:
	static void chooseMode();
	static void menu();
	static void instructions();
	static void lose();
	static void won();
	static void pause(const Game& game);
	static void clearPause(const Game& game);
	static void chooseLevel();
	static void noFiles();
	static void score(const Game& game);
	static void lives(const Game& game);
	
};