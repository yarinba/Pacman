#pragma once

#include <cctype>
#include "Point.h"
#include "Enums.h"

class Pacman {
	int lives = 3;
	const char symbol = '@';
	const char arrowKeys[5] = { 'w', 'x', 'a', 'd', 's'};
	Point pos = Point(34, 17);
	Direction direction = Direction::NONE;
	Color color = Color::YELLOW;
public:
	Point getPos() const;
	Direction getDirection() const;
	Direction getDirection(char key) const;
	void setDirection(Direction _direction);
	void setColor(Color c);
	void move();
};