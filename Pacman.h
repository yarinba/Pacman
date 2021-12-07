#pragma once

#include <cctype>
#include "Point.h"
#include "Enums.h"

class Pacman {
	const char symbol = '@';
	const char arrowKeys[5] = { 'w', 'x', 'a', 'd', 's'};
	Point pos = Point(34, 17);
	Direction direction = Direction::NONE;
	Color color = Color::YELLOW;
public:
	Direction getDirection() const;
	Direction getDirection(char key) const;
	const Point& getPos() const;
	void setPos(int x, int y);
	void setDirection(Direction _direction);
	void setColor(Color c);
	void move();
};