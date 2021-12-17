#pragma once

#include <time.h> 
#include "Point.h"
#include "Map.h"
#include "Ghost.h"
#include "GhostNovice.h"
#include "GhostGood.h"
#include "GhostBest.h"
#include "Pacman.h"
#include "utils.h"
#include "Print.h"

class Game {
	enum { ESC = 27, BREADCRUMBS = 430 };
	bool isColored = true;
	bool isWon = false;
	bool isLose = false;
	int eatenBreadcrumbs = 0;
	int score = 0;
	int lives = 3;
	Map map;
	Pacman pacman;
	Ghost** ghosts;
	friend class Print;
private:
	void setNoColor();
	void setColor();
	void increaseScore();
	void increaseScore(int num);
	bool isBreadcrumb() const;
	bool isGhost() const;
	void handleHitGhost();
	void handleGhostsMovement(int numOfIterations);
	void hitESC(Direction prevPacmanDirection);
	void initCreatures(bool newGame = true);
	void chooseLevel();
	void setGhostsLevel(char level);
public:
	void init();
	bool menu();
	void run();
};