#pragma once

#include "Pacman.h"
#include "Ghost.h"
#include "Map.h"
#include "utils.h"
#include "Point.h"

class Game {
	enum { ESC = 27, BREADCRUMBS = 430 };
	bool isWon = false;
	bool isLose = false;
	int eatenBreadcrumbs = 0;
	int score = 0;
	Map map;
	Pacman pacman;
	Ghost ghosts[2] = {Ghost(Point(48,3)), Ghost(Point(50,3))};
private:
	void displayMenu();
	void printScore();
	void printLives();
	void setNoColor();
	void run();
	void increaseScore();
	void increaseScore(int num);
	bool isWall();
	bool isBreadcrumb();
	bool isGhost();
	Point calculateNextPos(Point pos, Direction dir);
public:
	void start();
};