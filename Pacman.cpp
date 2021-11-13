#include "Pacman.h"

Point Pacman::getPos() const{
	return pos;
}

Direction Pacman::getDirection() const {
	return direction;
}

Direction Pacman::getDirection(char key) const {
	for (int i = 0; i < 5; i++) {
		if (key == arrowKeys[i] || tolower(key) == arrowKeys[i])
			return (Direction)i;
	}
	return Direction::NONE;
}

void Pacman::setDirection(Direction _direction) {
	direction = _direction;
}

void Pacman::setColor(Color _color) {
	color = _color;
}


void Pacman::move() {
	pos.draw(' ');
	pos.move(direction);
	pos.draw(symbol, color);
}