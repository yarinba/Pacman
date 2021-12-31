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
#include <regex>
using std::vector;
using std::string;
using std::fstream;

class Game {
protected:
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
	fstream stepsFile;
	fstream resultFile;
	friend class Print;
	void setNoColor();
	void setColor();
	void increaseScore();
	void increaseScore(int num);
	bool isBreadcrumb() const;
	bool isGhost() const;
	virtual void manageFruit(int numOfIterations)=0;
	void createFruit();
	bool handleHitFruit();
	void handleHitGhost();
	virtual void handleGhostsMovement(int numOfIterations)=0;
	void setGhostsLevel(char level);
	void hitESC(Direction prevPacmanDirection);
	void initCreatures(bool newGame = true);
	void chooseLevel();
	void setMode();
	void getFiles();
	void init();
	virtual void run() = 0;
  
public:
	virtual void play()=0;
	bool menu();
	~Game() { delete[] ghosts; }
};