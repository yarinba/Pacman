#include "Creature.h"

Creature::Creature(Point _pos, Direction _direction, Color _color, const char _symbol) :
	pos(_pos), direction (_direction), color(_color), symbol(_symbol) {};


Direction Creature::getDirection() const {
	return direction;
}

const Point& Creature::getPos() const {
	return pos;
}

char Creature::getSymbol() const {
	return symbol;
}

void Creature::setPos(int x, int y) {
	pos.set(x, y);
}

void Creature::setPos(const Point& p) {
	pos.set(p.getX(), p.getY());
}

// Set an new random direction to Creature (different from its predecessor)
void Creature::setDirection() {
	Direction _direction;
	do {
		_direction = Direction(rand() % 4);
	} while (_direction == direction);
	direction = _direction;
}

void Creature::setDirection(Direction _direction) {
	direction = _direction;
}

void Creature::setSymbol(char _symbol) {
	symbol = _symbol;
}


void Creature::setColor(Color _color) {
	color = _color;
}

void Creature::move(Direction direction, bool isBreadcrumbPos, bool isSilentMode) {
	setDirection(direction);
	if (!isSilentMode) {
		if (isBreadcrumbPos) pos.draw('*');
		else pos.draw(' ');
	}
	pos.move(direction);
	if (!isSilentMode) pos.draw(symbol, color);
}
