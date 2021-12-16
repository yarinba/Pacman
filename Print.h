#pragma once

#include "utils.h"
#include "Game.h"

class Game;

class Print {
public:
	static void menu();
	static void instructions();
	static void lose();
	static void won();
	static void pause();
	static void clearPause();
	static void chooseLevel();
	static void noFiles();
	static void score(const Game& game);
	static void lives(const Game& game);
	
};