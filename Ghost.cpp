#include "Ghost.h"

Ghost::Ghost(Point coord) {
	pos = coord;
	direction = Direction(rand() % 4);
}

const Point& Ghost::getPos() const {
	return pos;
}

Direction Ghost::getDirection() const {
	return direction;
}

void Ghost::setPos(int x, int y) {
	pos.set(x, y);
}

// Set an new random direction to Ghost (different from its predecessor)
void Ghost::setDirection() {
	Direction _direction;
	do {
		_direction = Direction(rand() % 4);
	} while (_direction == direction);
	direction = _direction;
}

void Ghost::setDirection(Direction _direction) {
	direction = _direction;
}

void Ghost::setColor(Color _color) {
	color = _color;
}

/*
* Get: boolean that represents whether the Ghost stepped on breadcrumb or not
* Move the Ghost position by 3 steps:
*	1a. if true - print breadcrumb at current position
*	1b. if false - print blank space at current position
*	2. change logical position
*	3. print the Pacman symbol at new logical position
*/
void Ghost::move(bool posIsBreadcrumb) {
	if (posIsBreadcrumb) pos.draw('*');
	else pos.draw(' ');
	pos.move(direction);
	pos.draw(symbol, color);
}