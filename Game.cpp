#include "Game.h"

void Game::setNoColor() {
	map.setIsColored(false);
	pacman.setColor(Color::WHITE);
	ghosts[0].setColor(Color::WHITE);
	ghosts[1].setColor(Color::WHITE);
}

void Game::increaseScore() {
	score++;
	printScore();
}

void Game::increaseScore(int num) {
	score += num;
}
 
Point Game::calculateNextPos(Point pos, Direction dir) {

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
		return pos;
		break;
	default:
		break;
	}
	return nextPos;
}

bool Game::isWall() {
	Point nextPos = calculateNextPos(pacman.getPos(), pacman.getDirection());
	if (map.getPoint(nextPos) == '#')
		return true;
	return false;
}

bool Game::isBreadcrumb() {
	if (map.getPoint(pacman.getPos()) == '*') {
		map.setPoint(pacman.getPos(), ' ');
		return true;
	}
	return false;
}

bool Game::isGhost() {
	return false;
}

void Game::displayMenu() {
	std::cout << ">>>>>>>>>>>>>>>>>>>>>>> WELCOME TO PACAMAN <<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl
		<< "1. Start a new game (with colors)" << std::endl
		<< "2. Start a new game (without colors)" << std::endl
		<< "8. Present instructions and keys" << std::endl
		<< "9. EXIT" << std::endl;
}

void Game::start() {
	hideCursor();
	displayMenu();
	char key = _getch();

	switch (key)
	{
	case '1':
		run();
		break;
	case '2':
		setNoColor();
		run();
		break;
	case '8':
		// display instructions and keys
		break;
	case '9':
		exit(0);
		break;
	default:
		break;
	}
}

void Game::printScore() {
	gotoxy(0, 23);
	setTextColor(Color::WHITE);
	std::cout << "SCORE: " << score << std::endl;
}

void Game::run() {
	char key = ' ';
	Direction dir;

	clear_screen();
	map.draw();
	printScore();

	while (true) {
		if (_kbhit()) {
			key = _getch();
			if ((dir = pacman.getDirection(key)) != Direction::NONE) {
				pacman.setDirection(dir);
			}
		}

		if (isWall()) {
			pacman.setDirection(Direction::STAY);
		}
		else {
			pacman.move();
		}

		if (isBreadcrumb()) {
			eatenBreadcrumbs++;
			increaseScore();
		}
		if (isGhost()) {
			// handle ghost
		}

		Sleep(250);
	}
}
