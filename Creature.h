#pragma once

#include "Point.h"
#include "Enums.h"

class Creature {
protected:
	Point pos;
	Direction direction;
	Color color;
	char symbol;

public:
	Creature(Point _pos, Direction _direction, Color _color, const char _symbol);
	Direction getDirection() const;
	const Point& getPos() const;
	char getSymbol() const;
	void setPos(int x, int y);
	void setPos(const Point& p);
	void setDirection(Direction _direction);
	void setDirection();
	void setSymbol(char _symbol);
	void setColor(Color c);
	void move(Direction direction, bool isBreadcrumbPos, bool isSilentMode);
};