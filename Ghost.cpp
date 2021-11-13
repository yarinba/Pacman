#include "Ghost.h"



Ghost::Ghost(Point coord) {
	pos = coord;
}

Point Ghost::getPos() const {
	return pos;
}

void Ghost::setDirection(Direction _direction) {
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