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
	ScreenMode mode;
	char ghostLevel = '0';
	vector <string> screenFilesNames;
	Map map;
	Pacman pacman;
	Ghost** ghosts;
	Fruit fruit;
	fstream stepsFile;
	fstream resultFile;
	friend class Print;
	void setNoColor();
	void setColor();
	void increaseScore(bool isSilentMode = false);
	void increaseScore(int num, bool isSilentMode = false);
	bool isBreadcrumb() const;
	bool isGhost() const;
	void createFruit();
	bool handleHitFruit();
	void handleHitGhost(bool isSilentMode = false);
	void setGhostsLevel(char level);
	void hitESC(Direction prevPacmanDirection);
	void initCreatures(bool newGame = true);
	void chooseLevel();
	void setMode();
	void getScreenFiles();
	void init();
	virtual void run() = 0;
	virtual void openRecordingFiles(const string& screenName) = 0;
	void closeRecordingFiles();
  
public:
	virtual void play()=0;
	bool menu();
	~Game() {delete[] ghosts; }
};