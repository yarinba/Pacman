﻿#include "Game.h"

/* Private Functions */

void Game::setNoColor() {
	isColored = false;
	map.setIsColored(false);
	pacman.setColor(Color::WHITE);
	ghosts[0].setColor(Color::WHITE);
	ghosts[1].setColor(Color::WHITE);
}

// increase score by 1 and prints current score
void Game::increaseScore() {
	score++;
	printScore();
}

// increase score by given number and prints current score
void Game::increaseScore(int num) {
	score += num;
	printScore();
}

void Game::printScore() const {
	gotoxy(0, 23);
	setTextColor(Color::WHITE);
	std::cout << "SCORE: ";

	if (isColored) setTextColor(Color::GREEN);
	std::cout << score;
}

void Game::printLives() const {
	gotoxy(0, 24);
	setTextColor(Color::WHITE);
	std::cout << "LIVES:    ";

	gotoxy(7, 24);
	if (isColored) setTextColor(Color::RED);
	for (int i = 0; i < lives; i++) {
		std::cout << HEART;
	}
}

void Game::printMenu() const {
	clear_screen();
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> WELCOME TO PACAMAN <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "1. Start a new game (with colors)" << std::endl
		<< "2. Start a new game (without colors)" << std::endl
		<< "8. Present instructions and keys" << std::endl
		<< "9. EXIT" << std::endl;
}

void Game::printInstructions() const {
	clear_screen();
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> Instructions <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "Press any key to continue :)" << std::endl;
	char key = _getch();
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
		if (x == 0 || x == 21 || y == 0 || y == 61)
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

/* Public Functions */

void Game::init() {
	hideCursor();
	setTextColor(Color::WHITE);
	srand(time(NULL));
	ghosts[0].setDirection();
	ghosts[1].setDirection();
}

/*
* Displays the menu
* Return: true if the game should start, otherwise false 
*/
bool Game::menu() {
	printMenu();
	char key = _getch();

	switch (key)
	{
	case '1':
		return true;
		break;
	case '2':
		setNoColor();
		return true;
		break;
	case '8':
		printInstructions();
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
	printScore();
	printLives();


	while (!isLose && !isWon) {
		// Move the ghosts every 2nd iteration
		handleGhostsMovement(numOfIterations);

		if (_kbhit()) {
			key = _getch();
			if ((dir = pacman.getDirection(key)) != Direction::NONE) {
				pacman.setDirection(dir);
			}
		}

		if (isWall(pacman.getPos(), pacman.getDirection())) {
			pacman.setDirection(Direction::STAY);
		} else {
			pacman.move();
		}

		if (isBreadcrumb()) {
			map.setPoint(pacman.getPos(), ' ');
			eatenBreadcrumbs++;
			increaseScore();
		}
		if (isGhost()) {
			lives--;
			if (lives) {
				printLives();
			}
			else {
				isLose = true;
			}
		}

		numOfIterations++;
		Sleep(150);
	}
}
