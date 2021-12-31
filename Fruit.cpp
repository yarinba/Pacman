#include "Fruit.h"

Fruit::Fruit() : 
	Creature(Point(0,0), Direction::NONE, Color::LIGHTCYAN, (((rand() % 5) + 5) + '0')) {};

int Fruit::getFruitVal() {
	return (int)(symbol - '0');
}

bool Fruit::getIsAlive() {
	return isAlive;
}

void Fruit::setIsAlive(bool _isAlive, bool isBreadcrumbPos) {
	if (!_isAlive) {
		numOfMoves = 0;
		if (isAlive) {
			if (isBreadcrumbPos) pos.draw('*');
			else pos.draw(' ');
		}
	}
	else
		this->setSymbol((((rand() % 5) + 5) + '0'));
	isAlive = _isAlive;
}


/*
* Get: The map by reference and iteration number of game loop
* (*) Execute only every third loop beacuse the pace of Fruit is lower than the pace of the Pacman ang Ghost
* (*) Move the Fruit position by 3 steps:
*		1a. if the ghost steped on a breadcrumb - print breadcrumb at current position
*		1b. else - print blank space at current position
*		2. change logical position
*		3. print the Ghost symbol at new logical position
*/
void Fruit::move(const Map& map, int iterationNumber) {
	if (!(iterationNumber % 3)) {
		bool isBreadcrumbPos = Movement::noviceMove(*this, map, iterationNumber);
		if (isBreadcrumbPos) pos.draw('*');
		else pos.draw(' ');
		pos.move(direction);
		pos.draw(symbol, color);
		numOfMoves++;
	}
}