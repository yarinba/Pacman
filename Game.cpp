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
	fruit.setIsAlive(false);
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

void Game::handleHitFruit() {
	int numofGhosts = map.getNumOfGhosts(), i = 0;
	bool hitGhost = false, hitPacman = false;
	// Check Ghost hit Fruit
	while (!hitGhost && i < numofGhosts) {
		hitGhost = ghosts[i]->getPos() == fruit.getPos();
		i++;
	}
	if (hitGhost) 
		fruit.setIsAlive(false, map.getPoint(fruit.getPos()) == '*');

	// Check Pacman hit Fruit
	hitPacman = pacman.getPos() == fruit.getPos();
	if (hitPacman) {
		fruit.setIsAlive(false, map.getPoint(fruit.getPos()) == '*');
		increaseScore(fruit.getFruitVal());
	}
}

void Game::manageFruit(int numOfIterations) {
	bool iteration100 = numOfIterations % 200 == 100;
	bool alreadyExist = fruit.getIsAlive();
	if (!alreadyExist && iteration100)
		createFruit();
	else if (alreadyExist) {
		handleHitFruit();
		fruit.move(map, numOfIterations);

		if(fruit.getNumOfMoves() == 60)
			fruit.setIsAlive(false, map.getPoint(fruit.getPos()) == '*');
	}
}

/* Public Functions */

void Game::init() {
	isWon = false;
	isLose = false;
	eatenBreadcrumbs = 0;
	score = 0;
	lives = 3;

	//TODO: get file name from user
	map.init("pacman_a.txt");
	initCreatures();
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
	setGhostsLevel(key);
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
		manageFruit(numOfIterations);

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
		Sleep(150);
	}

	if (isLose)
		Print::lose();
	else if (isWon)
		Print::won();
	key = _getch();
}

