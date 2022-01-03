#include "Game.h"

/* Private Functions */

void Game::setNoColor() {
	int numofGhosts = map.getNumOfGhosts();
	isColored = false;
	map.setIsColored(false);
	pacman.setColor(Color::WHITE);
	fruit.setColor(Color::WHITE);
	for(int i=0; i< numofGhosts; i++)
		ghosts[i]->setColor(Color::WHITE);
}

void Game::setColor() {
	int numofGhosts = map.getNumOfGhosts();
	isColored = true;
	map.setIsColored(true);
	pacman.setColor(Color::YELLOW);
	fruit.setColor(Color::LIGHTCYAN);
	for (int i = 0; i < numofGhosts; i++)
		ghosts[i]->setColor(Color::LIGHTMAGENTA);
}

// increase score by 1 and prints current score
void Game::increaseScore(bool isSilentMode) {
	score++;
	if (!isSilentMode) Print::score(*this);
}

// increase score by given number and prints current score
void Game::increaseScore(int num, bool isSilentMode) {
	score += num;
	if (!isSilentMode) Print::score(*this);
}

// Return: true if the Pacman hits breadcrumb, otherwise false
bool Game::isBreadcrumb() const {
	if (map.getPoint(pacman.getPos()) == '*') {
		return true;
	}
	return false;
}

// Return: true if the Pacman hits one of the ghosts, otherwise false
bool Game::isGhost() const {
	int numofGhosts = map.getNumOfGhosts();
	for (int i = 0; i < numofGhosts; i++) {
		if (pacman.getPos() == ghosts[i]->getPos())
			return true;
	}
	return false;
}

// The game will be paused after Esc was hit
void Game::hitESC(Direction prevPacmanDirection) {
	char key = ' ';
	int numofGhosts = map.getNumOfGhosts();
	Print::pause(*this);
	pacman.setDirection(Direction::NONE);
	for (int i = 0; i < numofGhosts; i++)
		ghosts[i]->setDirection(Direction::NONE);
	do {
		key = _getch();
	} while (key != ESC);

	Print::clearPause(*this);
	pacman.setDirection(prevPacmanDirection);
}

// Initiallizing pacman position and array of ghosts
void Game::initCreatures(bool newGame) {
	int numofGhosts = map.getNumOfGhosts();
	pacman.setDirection(Direction::NONE);
	pacman.setPos(map.getPacmanPos());
	fruit.setIsAlive(false);
	if(newGame)
		ghosts = new Ghost*[numofGhosts];
	else {
		const Point* ghostsPos = map.getGhostsPos();
		for (int i = 0; i < numofGhosts; i++) {
			ghosts[i]->setPos(ghostsPos[i]);
			ghosts[i]->setDirection(Direction::NONE);
		}
	}
}

// Reducing lives by 1 
// Initiallize pacman and ghosts positions
void Game::handleHitGhost(bool isSilentMode) {
	lives--;
	initCreatures(false);
	if (!isSilentMode) {
		map.draw();
		Print::score(*this);
		Print::lives(*this);
	}
}

void Game::setGhostsLevel(char level) {
	int numofGhosts = map.getNumOfGhosts();
	int i;
	switch (level) {
	case '1':
		for (i = 0; i < numofGhosts; i++)
			ghosts[i] = new GhostNovice;
		break;
	case '2':
		for (i = 0; i < numofGhosts; i++)
			ghosts[i] = new GhostGood;
		break;
	case '3':
		for (i = 0; i < numofGhosts; i++)
			ghosts[i] = new GhostBest;
		break;
	}
	const Point* ghostsPos = map.getGhostsPos();
	for (int i = 0; i < numofGhosts; i++) {
		ghosts[i]->setPos(ghostsPos[i]);
		ghosts[i]->setDirection(Direction::NONE);
		ghosts[i]->setColor(isColored ? Color::LIGHTMAGENTA : Color::WHITE);
	}
}

void Game::createFruit() {
	Point p;
	int x = 0, y = 0;
	bool isValid = false; 
	do {
		int x = (rand() % (map.getColSize() - 1)) + 1;
		int y = (rand() % (map.getRowSize() - 1)) + 1;
		p = Point(x, y);
		isValid = map.getPoint(p) == '*' || map.getPoint(p) == ' ';
	} while (!isValid);
	fruit.setPos(p);
	fruit.setIsAlive(true);
}

bool Game::handleHitFruit() {
	int numofGhosts = map.getNumOfGhosts(), i = 0;
	bool hitGhost = false, hitPacman = false;
	// Check Ghost hit Fruit
	while (!hitGhost && i < numofGhosts) {
		hitGhost = ghosts[i]->getPos() == fruit.getPos();
		i++;
	}
	if (hitGhost)
		return true;
	// Check Pacman hit Fruit
	hitPacman = pacman.getPos() == fruit.getPos();
	if (hitPacman) {
		increaseScore(fruit.getFruitVal());
		return true;
	}
	return false;
}

/*This function getting the files names from the working directory and putting it in the array screenFilesNames*/
void Game::getScreenFiles() {
	screenFilesNames.clear();
	string path = "./";
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		string str = entry.path().string();
		if (str.find(".screen") != string::npos) {
			string str1 = str;
			screenFilesNames.push_back(str1);
		}
	}
}

void Game::chooseLevel() {
	char key;
	do {
		Print::chooseLevel();
		key = _getch();
	} while (key != '1' && key != '2' && key != '3');
	ghostLevel = key;
}

/*This function setting the game mode-all screens or a specific screen according to the user choice*/
void Game::setMode() {
	getScreenFiles();
	char key;
	if (screenFilesNames.size() == 0)
	{
		std::cout << ">>> No files found <<<" << std::endl;
		exit(1);
	}
	else {
		do {
			Print::chooseMode();
			key = _getch();
		} while (key != '1' && key != '2');
	}
	if (key == '1')
		mode = ScreenMode::ALL_FILES;
	else
		mode = ScreenMode::ONE_FILE;
}

/*This functon initiializing the game class members if the user started a new game*/
void Game::init() {
	currFile = 0;
	isWon = false;
	isLose = false;
	eatenBreadcrumbs = 0;
	score = 0;
	lives = 3;
	hideCursor();
	setTextColor(Color::WHITE);
	srand(time(NULL));
}

void Game::closeRecordingFiles() {
	if (stepsFile.is_open())
		stepsFile.close();
	if (resultFile.is_open())
		resultFile.close();
}

/* Public Functions */

/*
* Displays the menu
* Return: true if the game should start, otherwise false
*/
bool Game::menu() {
	Print::menu();
	char key = _getch();
	switch (key)
	{
	case '1':
		setMode();
		chooseLevel();
		setColor();
		return true;
		break;
	case '2':
		setMode();
		chooseLevel();
		setNoColor();
		return true;
		break;
	case '8':
		Print::instructions();
		return false;
		break;
	case '9':
		exit(0);
		break;
	default:
		return false;
		break;
	}
	
}
