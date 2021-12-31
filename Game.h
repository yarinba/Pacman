#pragma once

#include <time.h> 
#include "Point.h"
#include "Map.h"
#include "Ghost.h"
#include "GhostNovice.h"
#include "GhostGood.h"
#include "GhostBest.h"
#include "Pacman.h"
#include "Fruit.h"
#include "utils.h"
#include "Print.h"
#include <vector>
#include <string>
#include <filesystem>
using std::vector;
using std::string;

class Game {
	enum { ESC = 27 };
	bool isColored = true;
	bool isWon = false;
	bool isLose = false;
	int eatenBreadcrumbs = 0;
	int score = 0;
	int lives = 3;
	int currFile = 0;
	Mode mode;
	char ghostLevel = '0';
	vector <string> fileNames;
	Map map;
	Pacman pacman;
	Ghost** ghosts;
	Fruit fruit;
	friend class Print;
private:
	void setNoColor();
	void setColor();
	void increaseScore();
	void increaseScore(int num);
	bool isBreadcrumb() const;
	bool isGhost() const;
	void manageFruit(int numOfIterations);
	void createFruit();
	void handleHitFruit();
	void handleHitGhost();
	void handleGhostsMovement(int numOfIterations);
	void setGhostsLevel(char level);
	void hitESC(Direction prevPacmanDirection);
	void initCreatures(bool newGame = true);
	void chooseLevel();
	void setMode();
	void getFiles();
	void init();
	void run();
  
public:
	void playChosenMode();
	bool menu();
	~Game() { delete[] ghosts; }
};