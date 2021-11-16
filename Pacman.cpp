#include "Pacman.h"

// Return the Pacman direction
Direction Pacman::getDirection() const {
	return direction;
}

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

Point Pacman::getPos() const {
	return pos;
}

void Pacman::setPos(int x, int y) {
	pos.set(x, y);
}

void Pacman::setDirection(Direction _direction) {
	direction = _direction;
}

void Pacman::setColor(Color _color) {
	color = _color;
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