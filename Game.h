#pragma once

#include <time.h> 
#include "Pacman.h"
#include "Ghost.h"
#include "Map.h"
#include "utils.h"
#include "Point.h"

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
	Ghost ghosts[2] = {Ghost(Point(48,3)), Ghost(Point(50,3))};
private:
	void setNoColor();
	void increaseScore();
	void increaseScore(int num);
	void printScore() const;
	void printLives() const;
	void printMenu() const;
	void printInstructions() const;
	Point calculateNextPos(Point pos, Direction dir) const;
	bool isWall(Point pos, Direction dir, bool isPacman = true) const;
	bool isBreadcrumb() const;
	bool isGhost() const;
	void handleGhostsMovement(int numOfIterations);
public:
	void init();
	bool menu();
	void run();
};