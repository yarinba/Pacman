#include "Game.h"

/* Private Functions */

void Game::setNoColor() {
	int numofGhosts = map.getNumOfGhosts();
	isColored = false;
	map.setIsColored(false);
	pacman.setColor(Color::WHITE);
	for(int i=0; i< numofGhosts; i++)
		ghosts[i]->setColor(Color::WHITE);
}

void Game::setColor() {
	int numofGhosts = map.getNumOfGhosts();
	isColored = true;
	map.setIsColored(true);
	pacman.setColor(Color::YELLOW);
	for (int i = 0; i < numofGhosts; i++)
		ghosts[i]->setColor(Color::LIGHTMAGENTA);
}

// increase score by 1 and prints current score
void Game::increaseScore() {
	score++;
	Print::score(*this);
}

// increase score by given number and prints current score
void Game::increaseScore(int num) {
	score += num;
	Print::score(*this);
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

/*
* Get: the number of the current iteration in the game loop
* Execute only every second loop beacuse the pace of Ghost is half the pace of the Pacman
*/
void Game::handleGhostsMovement(int numOfIterations) {
	int numofGhosts = map.getNumOfGhosts();
	if (!(numOfIterations % 2)) {
		for (int i = 0; i < numofGhosts; i++)
			ghosts[i]->move(map, pacman.getPos(), numOfIterations);
	}
}

// The game will be paused after Esc was hit
void Game::hitESC(Direction prevPacmanDirection) {
	char key = ' ';
	int numofGhosts = map.getNumOfGhosts();
	Print::pause();
	pacman.setDirection(Direction::NONE);
	for (int i = 0; i < numofGhosts; i++)
		ghosts[i]->setDirection(Direction::NONE);
	do {
		key = _getch();
	} while (key != ESC);

	Print::clearPause();
	pacman.setDirection(prevPacmanDirection);
}

// Initiallizing pacman position and array of ghosts
void Game::initCreatures(bool newGame) {
	int numofGhosts = map.getNumOfGhosts();
	pacman.setDirection(Direction::NONE);
	pacman.setPos(map.getPacmanPos());
	//TODO: delete previous allocation if exits
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
void Game::handleHitGhost() {
	lives--;
	initCreatures(false);
	map.draw();
}

void Game::setGhostsLevel(char level) {
	//TODO: get num of ghosts from board !!!
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
	}
}

/* Public Functions */

void Game::init() {
	isWon = false;
	isLose = false;
	eatenBreadcrumbs = 0;
	score = 0;
	lives = 3;
	hideCursor();
	setTextColor(Color::WHITE);
	srand(time(NULL));
}

/*
* Displays the menu
* Return: true if the game should start, otherwise false
*/
bool Game::menu() {
	Print::menu();
	char key = _getch();
	chooseLevel();
	setMode();
	switch (key)
	{
	case '1':
		setColor();
		return true;
		break;
	case '2':
		setNoColor();
		return true;
		break;
	case '3':
		setColor();
		return true;
		break;
	case '4':
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

void Game::chooseLevel() {
	char key;
	do {
		Print::chooseLevel();
		key = _getch();
	} while (key != '1' && key != '2' && key != '3');
	ghostLevel = key;
}

//seperate to 2 functions
void Game::setMode() {
	getFiles();
	int key;
	if (fileNames.size() == 0)
		std::cout << ">>No files found<<" << std::endl;
	else {
		do {
			Print::chooseMode();
			key = _getch();
		} while (key != '1' && key != '2');
	}
	if (key == '2')
		mode = 1;
}

	

void Game::playChosenMode() {
	string screen;
	bool found = false;
	int filesSize = fileNames.size();
	int i = 0;
	if (mode == 1)
	{
		
		do {
			clear_screen();
			std::cout << "Enter the screen name" << std::endl;
			std::cin >> screen;
			while (i < filesSize) {
				if (screen == fileNames[i]) {
					found = true;
					break;
				}
				i++;
			}
			i = 0;
		} while (!found);
		init();
		map.init(screen);
		initCreatures();
		setGhostsLevel(ghostLevel);
		run();
	}
	else
	{
		init();
		while ((currFile < filesSize) && (!isLose))
		{
			eatenBreadcrumbs = 0;
			isWon = false;
			map.init(fileNames[currFile]);
			initCreatures();
			setGhostsLevel(ghostLevel);
			run();
		}
	}
}

void Game::getFiles() {
	string str1;

	string path = "./";
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::filesystem::path str = entry.path();
		if (str.extension() == ".txt")
		{
			str1 = str.string();
		    fileNames.push_back(str1);
		}

	}
}



void Game::run() {
	int numOfIterations = 0;
	char key = ' ';
	Direction dir;

	clear_screen();
	map.draw();
	Print::score(*this);
	Print::lives(*this);


	while (!isLose && !isWon) {
		// Move the ghosts every 2nd iteration
		handleGhostsMovement(numOfIterations);

		if (_kbhit()) {
			key = _getch();
			if (key == ESC) {
				hitESC(pacman.getDirection()); /*pause the game*/
			}
			else if ((dir = pacman.getDirection(key)) != Direction::NONE) {
				pacman.setDirection(dir);
			}
		}

		/*if pacman hits a wall than he will stop*/
		if (map.isWall(pacman.getPos(), pacman.getDirection())) {
			pacman.setDirection(Direction::STAY);
		}
		else {
			pacman.move();
		}

		// Check if pacman ate breadcrumb
		if (isBreadcrumb()) {
			map.setPoint(pacman.getPos(), ' ');
			eatenBreadcrumbs++;
			increaseScore();
			if (eatenBreadcrumbs == map.getNumOfBreadCrumbs())
				isWon = true;
		}
		// Check if pacman hit ghost
		if (isGhost()) {
			handleHitGhost();
			if (lives) {
				Print::lives(*this);
			}
			else {
				isLose = true;
			}
		}

		numOfIterations++;
		Sleep(75);
	}

	if (isLose)
		Print::lose();
	else if ((isWon) && (mode == 1)) {
		Print::won();
		key = _getch();
	}
	else if ((isWon) && (mode == 0))
	{
		currFile++;
		if (currFile >= fileNames.size()) {
			Print::won();
			key = _getch();
		}
	}
}

