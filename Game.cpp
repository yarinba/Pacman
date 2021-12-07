#include "Game.h"

/* Private Functions */

void Game::setNoColor() {
	isColored = false;
	map.setIsColored(false);
	pacman.setColor(Color::WHITE);
	ghosts[0].setColor(Color::WHITE);
	ghosts[1].setColor(Color::WHITE);
}

void Game::setColor() {
	isColored = true;
	map.setIsColored(true);
	pacman.setColor(Color::YELLOW);
	ghosts[0].setColor(Color::LIGHTMAGENTA);
	ghosts[1].setColor(Color::LIGHTMAGENTA);
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

/*
* Get: current position and direction
* Return: Point represents the next move of given position
*/
Point Game::calculateNextPos(Point pos, Direction dir) const {

	Point nextPos;
	switch (dir)
	{
	case Direction::UP:
		nextPos.set(pos.getX(), pos.getY() - 1);
		break;
	case Direction::DOWN:
		nextPos.set(pos.getX(), pos.getY() + 1);
		break;
	case Direction::LEFT:
		nextPos.set(pos.getX() - 1, pos.getY());
		break;
	case Direction::RIGHT:
		nextPos.set(pos.getX() + 1, pos.getY());
		break;
	case Direction::STAY:
	case Direction::NONE:
		return pos;
		break;
	default:
		break;
	}
	return nextPos;
}

/*
* Get: current position, direction and boolean if the Player is Pacman or Ghost
* Return: true if the player will hit the wall, otherwise false
*/
bool Game::isWall(Point pos, Direction dir, bool isPacman) const {
	Point nextPos = calculateNextPos(pos, dir);
	//  Ghosts cannot cross in the invisible tunnels!
	if (!isPacman) {
		int x = nextPos.getX();
		int y = nextPos.getY();
		if (y == 0 || y == MAP_BOUNDARIES::Y - 1 || x == 0 || x == MAP_BOUNDARIES::X - 1)
			return true;
	}
	if (map.getPoint(nextPos) == '#')
		return true;
	return false;
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
	for (int i = 0; i < 2; i++) {
		if (pacman.getPos() == ghosts[i].getPos())
			return true;
	}
	return false;
}

/*
* Get: the number of the current iteration in the game loop
* Will execute only every second loop beacuse the pace of Ghost is half the pace of the Pacman
*/
void Game::handleGhostsMovement(int numOfIterations) {
	bool isBreadcrumbPos = false;
	if (!(numOfIterations % 2)) {
		for (int i = 0; i < 2; i++) {
			// Change the direction of the ghost if it hits the wall
			while (isWall(ghosts[i].getPos(), ghosts[i].getDirection(), false)) {
				ghosts[i].setDirection();
			}
			// Boolean - true if the Ghost stepped on a breadcrumb, otherwise false
			isBreadcrumbPos = (map.getPoint(ghosts[i].getPos()) == '*');
			ghosts[i].move(isBreadcrumbPos);
		}

		if (!(numOfIterations % 20)) {
			ghosts[0].setDirection();
			ghosts[1].setDirection();
		}
	}
}

/*if the player hits Esc than the game will be paused*/
void Game::hitESC(Direction prevPacmanDirection) {
	char key = ' ';
	Print::pause();
	pacman.setDirection(Direction::NONE);
	ghosts[0].setDirection(Direction::NONE);
	ghosts[1].setDirection(Direction::NONE);
	do {
		key = _getch();
	} while (key != ESC);

  /*returning ghost and pacman their original direction*/
	Print::clearPause();
	ghosts[0].setDirection();
	ghosts[1].setDirection();
	pacman.setDirection(prevPacmanDirection);
}

/*This function initiallizing the positions of the ghosts and pacman*/
void Game::initCreatures() {
	pacman.setDirection(Direction::NONE);
	pacman.setPos(34, 17);
	ghosts[0].setPos(48, 3);
	ghosts[1].setPos(50, 3);
	ghosts[0].setDirection();
	ghosts[1].setDirection();
}

/*This function reducing the number of lives by 1 and returning pacman and the ghosts to their starting point in case that pacman hits a ghost*/
void Game::handleHitGhost() {
	lives--;
	initCreatures();
	map.draw();
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
		if (isWall(pacman.getPos(), pacman.getDirection())) {
			pacman.setDirection(Direction::STAY);
		}
		else {
			pacman.move();
		}

		/*if pacman ate breadcrumb*/
		if (isBreadcrumb()) {
			map.setPoint(pacman.getPos(), ' ');
			eatenBreadcrumbs++;
			increaseScore();
			if (eatenBreadcrumbs == BREADCRUMBS)
				isWon = true;
		}
		/*if pacman hit a ghost*/
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
