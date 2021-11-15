#include "Ghost.h"

Ghost::Ghost(Point coord) {
	pos = coord;
	direction = Direction(rand() % 4);
}

Point Ghost::getPos() const {
	return pos;
}

Direction Ghost::getDirection() const {
	return direction;
}

void Ghost::setDirection() {
	Direction _direction;
	do {
		_direction = Direction(rand() % 4);
	} while (_direction == direction);
	direction = _direction;
}

void Ghost::setColor(Color _color) {
	color = _color;
}

void Ghost::move(bool posIsBreadcrumb) {
	if (posIsBreadcrumb) pos.draw('*');
	else pos.draw(' ');
	pos.move(direction);
	pos.draw(symbol, color);
}