#include "Game.h"

/* Private Functions */

void Game::setNoColor() {
	isColored = false;
	map.setIsColored(false);
	pacman.setColor(Color::WHITE);
	for(int i=0; i<map.numOfGhosts; i++)
		ghosts[i]->setColor(Color::WHITE);
}

void Game::setColor() {
	isColored = true;
	map.setIsColored(true);
	pacman.setColor(Color::YELLOW);
	for (int i = 0; i < map.numOfGhosts; i++)
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
	for (int i = 0; i < map.numOfGhosts; i++) {
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
	if (!(numOfIterations % 2)) {
		for (int i = 0; i < map.numOfGhosts; i++)
			ghosts[i]->move(map, pacman.getPos(), numOfIterations);
	}
}

// The game will be paused after Esc was hit
void Game::hitESC(Direction prevPacmanDirection) {
	char key = ' ';
	Print::pause();
	pacman.setDirection(Direction::NONE);
	for (int i = 0; i < map.numOfGhosts; i++)
		ghosts[i]->setDirection(Direction::NONE);
	do {
		key = _getch();
	} while (key != ESC);

	Print::clearPause();
	pacman.setDirection(prevPacmanDirection);
}

// Initiallizing pacman position and array of ghosts
void Game::initCreatures(bool newGame) {
	pacman.setDirection(Direction::NONE);
	pacman.setPos(map.pacmanLocation);
	//TODO: delete previous allocation if exits
	if(newGame)
		ghosts = new Ghost*[map.numOfGhosts];
	else {
		for (int i = 0; i < map.numOfGhosts; i++) {
			ghosts[i]->setPos(map.GhostsLocations[i]);
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
	int numofGhosts = map.numOfGhosts;
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

	for (int i = 0; i < map.numOfGhosts; i++) {
		ghosts[i]->setPos(map.GhostsLocations[i]);
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

	map.init();
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
			if (eatenBreadcrumbs == BREADCRUMBS)
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

