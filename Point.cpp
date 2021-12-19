#include "Point.h"

bool operator== (const Point& p1, const Point& p2) {
	return (p1.x == p2.x && p1.y == p2.y);
}

Point::Point(): Point(0, 0) {}

Point::Point(int _x, int _y) : x(_x), y(_y) {}

int Point::getX() const {
	return x;
}

int Point::getY() const {
	return y;
}

void Point::set(int _x, int _y) {
	x = _x;
	y = _y;
}

// Get: direction - change Point position Respectively
void Point::move(Direction dir, int rowSize, int colSize) {
	bool isPacman = false;
	if (rowSize != 0 && colSize != 0)
		isPacman = true;
	switch (dir) {
	case Direction::UP:
		--y;
		if (isPacman && y < 0) {
			y = rowSize - 1;
		}
		break;
	case Direction::DOWN:
		++y;
		if (isPacman && y > rowSize - 1) {
			y = 0;
		}
		break;
	case Direction::LEFT:
		--x;
		if (isPacman && x < 0) {
			x = colSize - 1;
		}
		break;
	case Direction::RIGHT:
		++x;
		if (isPacman && x > colSize - 1) {
			x = 0;
		}
		break;
	}
}

// Get: char symbol and color - prints it at the Point position
void Point::draw(char ch, Color color) const {
	setTextColor(color);
	gotoxy(x, y);
	std::cout << ch;
}