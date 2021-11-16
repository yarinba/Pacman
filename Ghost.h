#pragma once

#include "Point.h"
#include "Enums.h"

class Ghost {
	const char symbol = '$';
	Point pos;
	Direction direction = Direction::NONE;
	Color color = Color::LIGHTMAGENTA;

public:
	Ghost(Point coord);
	Point getPos() const;
	Direction getDirection() const;
	void setPos(int x, int y);
	void setDirection();
	void setDirection(Direction _direction);
	void setColor(Color _color);
	void move(bool posIsBreadcrumb);
};