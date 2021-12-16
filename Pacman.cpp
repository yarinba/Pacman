#include "Pacman.h"

Pacman::Pacman(): 
	Creature(Point(34, 17), Direction::NONE, Color::YELLOW, '@') {}

/*
* Get: key pressed by the user
* Return: direction corresponding to the key
*/
Direction Pacman::getDirection(char key) const {
	for (int i = 0; i < 5; i++) {
		if (key == arrowKeys[i] || tolower(key) == arrowKeys[i])
			return (Direction)i;
	}
	return Direction::NONE;
}

/*
* Move the Pacman position by 3 steps:
*	1. print blank space at current position
*	2. change logical position
*	3. print the Pacman symbol at new logical position
*/
void Pacman::move() {
	pos.draw(' ');
	pos.move(direction);
	pos.draw(symbol, color);
}