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
	void setDirection();
	void setColor(Color _color);
	void move(bool posIsBreadcrumb);
};