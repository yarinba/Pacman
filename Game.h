#pragma once

#include "Pacman.h"
#include "Ghost.h"
#include "Map.h"

class Game {
	enum { ESC = 27 };
	bool isColored = true;
	bool isWon = false;
	bool isLose = false;
	Map map;
	Pacman pacman;
	//Ghost ghosts[2];
private:
	void setIsColored(bool _isColored) {
		isColored = _isColored;
	}
public:
	void init();
	void run();
};